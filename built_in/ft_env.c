/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/05 11:01:50 by malavaud          #+#    #+#             */
/*   Updated: 2026/05/05 11:01:50 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_env(char **env, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->args[1])
	{
		ft_putstr_fd("env: '", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd("': No such file or directory\n", 2);
		return (127);
	}
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
