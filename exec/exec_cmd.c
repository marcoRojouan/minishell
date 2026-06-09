/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 14:05:10 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/09 14:15:09 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	setup_redirections(t_cmd *cmd, t_shell *shell)
{
	int	fd;

	if (cmd->fd_heredoc != -1)
		dup2(cmd->fd_heredoc, STDIN_FILENO);
	if (cmd->outfile) /*si la cmd contient > >>*/
	{
		if (cmd->insert)/*cas avec >> o_append ecrit a la fin du ficher*/
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else /*cas avc > o_trunc ecrase le contenu du fichier avant d'ecrire*/
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(cmd->outfile);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);/*remplace stout par le fichier*/
		close(fd);
	}
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);/*ouvre le fichier en lecture*/
		if (fd < 0)
		{
			perror(cmd->infile);
			cleanup_child(shell, NULL);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);/*remplace stdin par le fichier */
		close(fd);
	}
}

//void	exec_cmd(t_cmd *cmd, t_shell *shell)
//{
//	char	*path;

//	if (!cmd->args || !cmd->args[0])
//		exit(1);
//	setup_redirections(cmd);
//	if (exec_child_builtin(cmd, shell))
//		exit(0);
//	path = find_path(cmd->args[0], shell->env);
//	if (!path)
//	{
//		printf("minishell: command not found: %s\n", cmd->args[0]);
//		exit(127);
//	}
//	execve(path, cmd->args, shell->env);
//	perror("execve");
//	free(path);
//	exit (1);
//}
void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	signal(SIGPIPE, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	path = NULL;
	if (!cmd->args || !cmd->args[0])
	{
		cleanup_child(shell, NULL);
		exit(1);
	}
	setup_redirections(cmd, shell);
	if (exec_child_builtin(cmd, shell))
	{
		cleanup_child(shell, NULL);
		exit(0);
	}
	path = find_path(cmd->args[0], shell->env);
	if (!path)
	{
		write(STDERR_FILENO, "minishell: command not found: ", 31);
		write(STDERR_FILENO, cmd->args[0], strlen(cmd->args[0]));
		write(STDERR_FILENO, "\n", 1);
		cleanup_child(shell, NULL);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror("execve");
	cleanup_child(shell, path);
	exit(1);
}
