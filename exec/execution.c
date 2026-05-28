/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:14:27 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/28 11:57:37 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// variable globale pour le statut, on sait pas mais peut etre

static int     exec_builtin(t_shell *shell)
{
    char    *cmd;

    cmd = shell->cmds[0]->args[0];
    printf("%s", cmd);
    if (ft_strcmp(cmd, "pwd") == 0)
        return (ft_pwd());
    else if (ft_strcmp(cmd, "env") == 0)
        return (ft_env(shell->env), 1);
    else if (ft_strcmp(cmd, "export") == 0)
        return (ft_export(shell->cmds[0]->args, shell->env), 1);
    else if (ft_strcmp(cmd, "unset") == 0)
        return (ft_unset(shell->cmds[0]->args, shell->env), 1);
    else if (ft_strcmp(cmd, "echo") == 0)
        return (ft_echo(shell->cmds[0]->args), 1);
    else if (ft_strcmp(cmd, "cd") == 0)
        return (ft_cd(shell->cmds[0]->args, shell->env), 1);
    return (0);
}

int	execution(t_shell *shell)
{
    
	if (shell->cmd_count == 1)
	{
		if (!exec_builtin(shell))
            exec_one_cmd(shell);
	}
	else
		exec_pipeline(shell);
	// // on essai a chaque step de recuperer le STATUT;
	return (1);
}
