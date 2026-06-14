/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/14 21:28:21 by loup              #+#    #+#             */
/*   Updated: 2026/06/14 21:28:21 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*get_env(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

char	**add_env(char **env, char *key, char *value, int i)
{
	char	**new_env;
	char	*new;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return (NULL);
	i = 0;
	while (env[i])
	{
		new_env[i] = env[i];
		i++;
	}
	new = malloc(ft_strlen(key) + ft_strlen(value) + 2);
	if (!new)
		return (NULL);
	ft_strcpy(new, key);
	ft_strcat(new, "=");
	ft_strcat(new, value);
	new_env[i] = new;
	new_env[i + 1] = NULL;
	free(env);
	return (new_env);
}

static char	**replace_env(char **env, char *key, char *value, int i)
{
	char	*new;
	int		len;

	len = ft_strlen(key);
	new = malloc(len + ft_strlen(value) + 2);
	if (!new)
		return (NULL);
	ft_strcpy(new, key);
	ft_strcat(new, "=");
	ft_strcat(new, value);
	free(env[i]);
	env[i] = new;
	return (env);
}

char	**set_env(char **env, char *key, char *value)
{
	int	i;
	int	len;

	i = 0;
	if (!value)
		return (env);
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0
			&& env[i][len] == '=')
			return (replace_env(env, key, value, i));
		i++;
	}
	return (add_env(env, key, value, i));
}
