/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:45:36 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/10 10:44:20 by malavaud         ###   ########.fr       */
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
	int	j;

	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = malloc(sizeof(int) * 2);
		if (!pipes[i])
		{
			j = 0;
			while (j < i)
			{
				free(pipes[j]);
				j++;
			}
			return (0);
		}
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

static void	fork_cmds(t_shell *shell, t_pipeline *pipeline)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		pipeline->pids[i] = fork();
		if (pipeline->pids[i] == 0)
		{
			fd_gestion(shell, pipeline->pipes, i);
			free_pipeline(pipeline);
			exec_cmd(shell->cmds[i], shell);
		}
		i++;
	}
}

int	exec_pipeline(t_shell *shell)
{
	t_pipeline	pipeline;

	pipeline.cmd_count = shell->cmd_count;
	pipeline.pids = malloc(sizeof(pid_t) * shell->cmd_count);
	if (!pipeline.pids)
		return (0);
	pipeline.pipes = malloc(sizeof(int *) * (shell->cmd_count - 1));
	if (!pipeline.pipes)
	{
		free(pipeline.pids);
		return (0);
	}
	if (!init_pipes(pipeline.pipes, shell->cmd_count))
	{
		free(pipeline.pipes);
		free(pipeline.pids);
		return (0);
	}
	fork_cmds(shell, &pipeline);
	close_pipes(pipeline.pipes, shell->cmd_count);
	free_pipes(&pipeline);
	wait_all(pipeline.pids, shell->cmd_count, shell);
	free(pipeline.pids);
	return (1);
}
