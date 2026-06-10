/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 14:05:10 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/10 10:32:57 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	setup_redirections(t_cmd *cmd, t_shell *shell)
{
	int	fd;

	if (cmd->fd_heredoc != -1)
		dup2(cmd->fd_heredoc, STDIN_FILENO);
	if (cmd->outfile)
	{
		if (cmd->insert)
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			fd = open(cmd->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd < 0)
		{
			perror(cmd->outfile);
			exit(1);
		}
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (cmd->infile)
	{
		fd = open(cmd->infile, O_RDONLY);
		if (fd < 0)
		{
			perror(cmd->infile);
			cleanup_child(shell, NULL);
			exit(1);
		}
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
}

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
