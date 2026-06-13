/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 16:45:23 by loup              #+#    #+#             */
/*   Updated: 2026/06/13 21:13:36 by malavaud         ###   ########.fr       */
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

static int	exec_env_builtin(char *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd, "cd") == 0)
		shell->env = ft_cd(shell->cmds[0]->args, shell->env);
	else if (ft_strcmp(cmd, "export") == 0)
		shell->env = ft_export(shell->cmds[0]->args, shell);
	else if (ft_strcmp(cmd, "unset") == 0)
		shell->env = ft_unset(shell->cmds[0]->args, shell->env, shell);
	else
		return (0);
	return (1);
}

int	exec_parent_builtin(t_shell *shell)
{
	char	*cmd;

	cmd = shell->cmds[0]->args[0];
	if (!cmd)
		return (0);
	if (exec_env_builtin(cmd, shell))
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
	{
		ft_exit(shell->cmds[0]->args, shell);
		return (1);
	}
	return (0);
}

int	exec_child_builtin(t_cmd *cmd, t_shell *shell)
{
	if (!cmd || !cmd->args || !cmd->args[0])
		return (-1);
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_echo(cmd->args), 0);
	else if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_pwd(), 0);
	else if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_env(shell->env, cmd));
	return (-1);
}
