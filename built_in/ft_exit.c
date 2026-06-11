/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:41:35 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/10 21:05:44 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_shell(t_shell *shell, int status)
{
	ft_free_tab(shell->env);
	free_export_env(shell);
	free_cmds(shell);
	exit(status);
}

int	ft_exit(char **args, t_shell *shell)
{
	int	status;

	printf("exit\n");
	if (!args[1])
		exit_shell(shell, shell->exit_status);
	if (!is_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required\n", args[1]);
		exit_shell(shell, 2);
	}
	if (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return (1);
	}
	status = ft_atoi(args[1]) % 256;
	exit_shell(shell, status);
	return (0);
}
