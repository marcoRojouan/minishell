/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:41:35 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/04 11:52:08 by malavaud         ###   ########.fr       */
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

int	ft_exit(char **args, t_shell *shell)
{
	printf("exit\n");
	if (!args[1])
		exit(shell->exit_status);
	if (!is_numeric(args[1]))
	{
		printf("minishell: exit: %s: numeric argument required", args[1]);
		exit(2);
	}
	while (args[2])
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_status = 1;
		return (1);
	}
	exit(ft_atoi(args[1]) % 256);
}
