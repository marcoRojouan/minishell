/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 14:45:36 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/12 16:02:20 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_pipeline(t_shell *shell)
{
	pid_t *pids;
	int	**pipes;
	int	status;
	int	i;
	
	pipes = malloc(sizeof(int) * shell->cmd_count - 1);
	while (pipes[i])
	{
		pipes[i] = malloc(sizeof(int) * 2);
		pipe(pipes[i]);
		i++;
	}
	i = 0;
	while (i < shell->cmd_count)
	{
		pids[i] = fork();
		i++;
	}
	i = 0;
	while (i < shell->cmd_count)
	{
		waitpid(pids[i], &status, 0);
		i++;
	}
	shell->exit_status = WEXITSTATUS(status);
}