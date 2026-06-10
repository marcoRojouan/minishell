/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_gestion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 15:03:40 by loup              #+#    #+#             */
/*   Updated: 2026/06/10 15:58:34 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	close_all_heredocs(t_shell *shell)
{
	int j;

	j = 0;
	while (j < shell->cmd_count)
	{
		if (shell->cmds[j]->fd_heredoc != -1)
		{
			close(shell->cmds[j]->fd_heredoc);
			shell->cmds[j]->fd_heredoc = -1;
		}
		j++;
	}
}

static void	setup_stdin(t_shell *shell, int **pipes, int i)
{
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	else if (shell->cmds[i]->fd_heredoc != -1)
	{
		dup2(shell->cmds[i]->fd_heredoc, STDIN_FILENO);
		close(shell->cmds[i]->fd_heredoc);
		shell->cmds[i]->fd_heredoc = -1;
	}
}

void	fd_gestion(t_shell *shell, int **pipes, int i)
{
	int j;

	setup_stdin(shell, pipes, i);
	if (i < shell->cmd_count - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < shell->cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	close_all_heredocs(shell);
}
