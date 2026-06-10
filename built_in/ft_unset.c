/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:27:35 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/10 10:45:20 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	unset_env(char **env, char *key)
{
	int		i;
	int		j;
	int		len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0
			&& env[i][len] == '=')
		{
			free(env[i]);
			j = i;
			while (env[j])
			{
				env[j] = env[j + 1];
				j++;
			}
			return ;
		}
		i++;
	}
}

char	**ft_unset(char **args, char **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (!valid_key(args[i]))
		{
			printf("unset: `%s': not a valid identifier\n", args[i]);
			i++;
			continue ;
		}
		unset_env(env, args[i]);
		i++;
	}
	return (env);
}
