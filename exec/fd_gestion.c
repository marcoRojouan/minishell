/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_gestion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 15:03:40 by loup              #+#    #+#             */
/*   Updated: 2026/05/24 15:10:45 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int fd_gestion(t_shell *shell, int **pipes, int i)
{
    int	j;

	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < shell->cmd_count - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < shell->cmd_count - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
}