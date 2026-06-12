/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/04 10:27:35 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/12 10:55:04 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	unset_export(t_shell *shell, char *key)
{
	int	i;
	int	j;

	i = 0;
	while (i < shell->export_count)
	{
		if (!ft_strcmp(shell->export_env[i].key, key))
		{
			free(shell->export_env[i].key);
			free(shell->export_env[i].value);
			j = i;
			while (j < shell->export_count - 1)
			{
				shell->export_env[j] = shell->export_env[j + 1];
				j++;
			}
			shell->export_count--;
			return ;
		}
		i++;
	}
}

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

char	**ft_unset(char **args, char **env, t_shell *shell)
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
		unset_export(shell, args[i]);
		i++;
	}
	return (env);
}
