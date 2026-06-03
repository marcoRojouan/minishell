/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:45:23 by loup              #+#    #+#             */
/*   Updated: 2026/06/03 14:04:38 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_parent_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	exec_parent_builtin(t_shell *shell)
{
	char	*cmd;

	cmd = shell->cmds[0]->args[0];
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell->cmds[0]->args, shell->env), 1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(shell->cmds[0]->args, shell->env), 1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(shell->cmds[0]->args, shell->env), 1);
	return (0);
}

int	exec_child_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (0);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd->args), 1);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd(), 1);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(shell->env), 1);
	return (0);
}
