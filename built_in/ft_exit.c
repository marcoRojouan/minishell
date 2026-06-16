/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:51:48 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/16 10:54:21 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	parse_exit_value(char *str, long long *result)
{
	int			sign;
	int			i;
	long long	nb;

	sign = 1;
	i = 0;
	nb = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i])
	{
		if (nb > LLONG_MAX / 10
			|| (nb == LLONG_MAX / 10
				&& str[i] - '0' > LLONG_MAX % 10))
			return (0);
		nb = nb * 10 + (str[i] - '0');
		i++;
	}
	*result = nb * sign;
	return (1);
}

static int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (!str || !str[i])
		return (0);
	if (str[i] == '-' || str[i] == '+')
	{
		i++;
		if (!str[i])
			return (0);
	}
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
	int			status;
	long long	value;

	printf("exit\n");
	if (!args[1])
		exit_shell(shell, shell->exit_status);
	if (!is_numeric(args[1]) || !parse_exit_value(args[1], &value))
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
