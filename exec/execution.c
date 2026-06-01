/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:14:27 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/01 15:18:41 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execution(t_shell *shell)
{
	if (!prepare_heredoc(shell))
	{
		return (1);
	}
	if (!shell->cmds[0]->args || !shell->cmds[0]->args[0])
		return (1);
	if (shell->cmd_count == 1)
	{
		if (is_parent_builtin(shell->cmds[0]->args[0]))
			exec_parent_builtin(shell);
		else
			exec_one_cmd(shell);
	}
	else
		exec_pipeline(shell);
	return (1);
}
