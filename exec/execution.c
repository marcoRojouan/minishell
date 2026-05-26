/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:14:27 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/26 16:05:08 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	exec_caller(t_shell *shell)
{
	if (shell->cmd_count == 1)
	{
		if (ft_strcmp(shell->cmds[0]->args[0], "pwd") == 0)
			ft_pwd();
		if (ft_strcmp(shell->cmds[0]->args[0], "env") == 0)
			ft_env(shell->env);
		if (ft_strcmp(shell->cmds[0]->args[0], "export") == 0)
			ft_export(shell->cmds[0]->args, shell->env);
		if (ft_strcmp(shell->cmds[0]->args[0], "unset") == 0)
			ft_unset(shell->cmds[0]->args, shell->env);
		if (ft_strcmp(shell->cmds[0]->args[0], "echo") == 0)
			ft_echo(shell->cmds[0]->args);
		if (ft_strcmp(shell->cmds[0]->args[0], "cd") == 0)
			ft_cd(shell->cmds[0]->args, shell->env);
		// si jamais la commande correspond a aucun builtin on envoi a l'exec d'1 commande
	}
	else
	{
		exec_pipeline(shell);
	}
	// on essai a chaque step de recuperer le STATUT
	return (1);
}
