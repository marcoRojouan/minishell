/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:48:48 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/10 11:55:02 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**handle_assignment(char *arg, char **env, char *ptr)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, ptr - arg);
	value = ptr + 1;
	if (!check_key(key))
		return (free(key), env);
	env = set_env(env, key, value);
	free(key);
	return (env);
}

static char	**handle_plus(char *arg, char **env)
{
	char	*ptr;
	char	*key;
	char	*value;
	char	*old;
	char	*tmp;

	ptr = ft_strnstr(arg, "+=", ft_strlen(arg));
	key = ft_substr(arg, 0, ptr - arg);
	value = ptr + 2;
	if (!check_key(key))
		return (free(key), env);
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

	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return (handle_plus(arg, env));
	ptr = ft_strchr(arg, '=');
	if (ptr)
		return (handle_assignment(arg, env, ptr));
	if (!check_key(arg))
		return (env);
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
