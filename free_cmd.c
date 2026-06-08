/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 14:14:37 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/07 17:24:58 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_cmd(t_cmd *cmd)
{
	int	i;

	if (!cmd)
		return ;
	if (cmd->args)
	{
		i = 0;
		while (cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
	}
	free(cmd);
}

void	free_cmds(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		free_cmd(shell->cmds[i]);
		i++;
	}
	free(shell->cmds);
	shell->cmds = NULL;
	shell->cmd_count = 0;
}
