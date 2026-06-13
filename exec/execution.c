/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:14:27 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/13 22:54:01 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	execution(t_shell *shell)
{
	signal(SIGPIPE, SIG_IGN);
	if (!prepare_heredoc(shell))
		return ;
	if (!shell->cmds[0]->args || !shell->cmds[0]->args[0])
		return ;
	if (shell->cmd_count == 1)
	{
		if (is_parent_builtin(shell->cmds[0]->args[0]))
			exec_parent_builtin(shell);
		else
			exec_one_cmd(shell);
	}
	else
		exec_pipeline(shell);
	if (g_signal == 130)
    g_signal = 0;
}
