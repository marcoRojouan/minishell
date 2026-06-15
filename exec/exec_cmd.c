/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 14:05:10 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/15 13:52:25 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	open_outfile(t_cmd *cmd, t_shell *shell)
{
	int	fd;
	int	flags;

	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (cmd->insert)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	fd = open(cmd->outfile, flags, 0644);
	if (fd < 0)
	{
		perror(cmd->outfile);
		cleanup_child(shell, NULL);
		exit(1);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	open_infile(t_cmd *cmd, t_shell *shell)
{
	int	fd;

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

void	setup_redirections(t_cmd *cmd, t_shell *shell)
{
	if (cmd->fd_heredoc != -1)
	{
		dup2(cmd->fd_heredoc, STDIN_FILENO);
		close(cmd->fd_heredoc);
	}
	if (cmd->outfile)
		open_outfile(cmd, shell);
	if (cmd->infile)
		open_infile(cmd, shell);
}

static void	run_execve(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = find_path(cmd->args[0], shell->env);
	if (!path)
	{
		write(STDERR_FILENO, "minishell: command not found: ", 30);
		write(STDERR_FILENO, cmd->args[0], ft_strlen(cmd->args[0]));
		write(STDERR_FILENO, "\n", 1);
		cleanup_child(shell, NULL);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror("execve");
	cleanup_child(shell, path);
	exit(1);
}

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	int	status;

	signal(SIGPIPE, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (!cmd->args || !cmd->args[0])
	{
		cleanup_child(shell, NULL);
		exit(1);
	}
	setup_redirections(cmd, shell);
	status = exec_child_builtin(cmd, shell);
	if (status >= 0)
	{
		cleanup_child(shell, NULL);
		exit(status);
	}
	run_execve(cmd, shell);
}
