/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:48:48 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/10 10:45:43 by malavaud         ###   ########.fr       */
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

static char	**handle_plus(char *arg, char **env)
{
	char	*ptr;
	char	*key;
	char	*value;
	char	*old;
	char	*tmp;

	ptr = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (!ptr)
		return (env);
	key = ft_substr(arg, 0, ptr - arg);
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

static char	**export_one_arg(char *arg, char **env)
{
	char	*ptr;
	char	*key;
	char	*value;

	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return (handle_plus(arg, env));
	ptr = ft_strchr(arg, '=');
	if (ptr)
	{
		key = ft_substr(arg, 0, ptr - arg);
		value = ptr + 1;
		if (!valid_key(key))
		{
			printf("export: `%s': not a valid identifier\n", key);
			free(key);
			return (env);
		}
		env = set_env(env, key, value);
		free(key);
		return (env);
	}
	if (!valid_key(arg))
	{
		printf("export: `%s': not a valid identifier\n", arg);
		return (env);
	}
	return (env);
}

char	**ft_export(char **args, char **env)
{
	int	i;

	if (!args[1])
	{
		ft_env(env);
		return (env);
	}
	i = 1;
	while (args[i])
	{
		env = export_one_arg(args[i], env);
		i++;
	}
	return (env);
}
