/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:48:48 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/08 14:26:09 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	valid_key(char *key)
{
	int	i;

	if (!key || !key[0])
		return (0);
	if (!(ft_isalpha(key[0]) || key[0] == '_'))
		return (0);
	i = 1;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static char	**handle_plus(char **args, char **env)
{
	char	*ptr;
	char	*key;
	char	*value;
	char	*old;
	char	*tmp;

	ptr = ft_strnstr(args[1], "+=", ft_strlen(args[1]));
	if (!ptr)
		return (env);
	key = ft_substr(args[1], 0, ptr - args[1]);
	value = ptr + 2;
	if (!valid_key(key))
	{
		printf("export: `%s': not a valid identifier\n", key);
		free(key);
		return (env);
	}
	old = get_env(env, key);
	if (old)
	{
		tmp = ft_strjoin(old, value);
		env = set_env(env, key, tmp);
		free(tmp);
	}
	else
		env = set_env(env, key, value);
	free(key);
	return (env);
}

char	**ft_export(char **args, char **env)
{
	char	*ptr;
	char	*key;
	char	*value;

	if (!args[1])
	{
		ft_env(env);
		return (env);
	}
	if (ft_strnstr(args[1], "+=", ft_strlen(args[1])))
		return (handle_plus(args, env));
	ptr = ft_strchr(args[1], '=');
	if (ptr)
	{
		key = ft_substr(args[1], 0, ptr - args[1]);
		value = ptr + 1;
		if (!valid_key(key))
		{
			return (printf("export: `%s': not a valid identifier\n", key), env);
			free(key);
			return (env);
		}
		env = set_env(env, key, value);
		free(key);
		return (env);
	}
	key = args[1];
	if (!valid_key(key))
		return (printf("export: `%s': not a valid identifier\n", key), env);
	env = set_env(env, key, "");
	return (env);
}
