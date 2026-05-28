/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:14:27 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/28 17:02:57 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	execution(t_shell *shell)
{
	char	*cmd;

	cmd = shell->cmds[0]->args[0];

	if (shell->cmd_count == 1)
	{
		if (is_parent_builtin(cmd))
			exec_parent_builtin(shell);
		else
            exec_cmd(shell->cmds[0], shell);
// exec_one_cmd(shell);
	}
	else
	{
		exec_pipeline(shell);
	}
	return (1);
}
