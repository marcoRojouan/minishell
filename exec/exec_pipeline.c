/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:45:36 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/07 22:08:41 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	wait_all(pid_t *pids, int cmd_count, t_shell *shell)
{
	int	status;
	int	i;

	i = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				write(1, "\n", 1);
				shell->exit_status = 128 + WTERMSIG(status);
			}
		}
		i++;
	}
}

static int	init_pipes(int **pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
			return (0);
		pipe(pipes[i]);
		i++;
	}
	return (1);
}

static void	close_pipes(int **pipes, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
}

static void	fork_cmds(t_shell *shell, int **pipes, pid_t *pids)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		pids[i] = fork();
		if (pids[i] == -1)
		{
			perror("fork");
			exit(1);
		}
		if (pids[i] == 0)
		{
			fd_gestion(shell, pipes, i);
			exec_cmd(shell->cmds[i], shell);
		}
		i++;
	}
}

int	exec_pipeline(t_shell *shell)
{
	pid_t	*pids;
	int		**pipes;

	pids = malloc(sizeof(pid_t) * shell->cmd_count);
	if (!pids)
		return (0);
	pipes = malloc(sizeof(int *) * (shell->cmd_count - 1));
	if (!pipes)
		return (0);
	if (!init_pipes(pipes, shell->cmd_count))
		return (0);
	fork_cmds(shell, pipes, pids);
	close_pipes(pipes, shell->cmd_count);
	wait_all(pids, shell->cmd_count, shell);
	return (1);
}
