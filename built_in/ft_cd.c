/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:30:37 by malavaud          #+#    #+#             */
/*   Updated: 2026/05/26 15:01:48 by malavaud         ###   ########.fr       */
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
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')/*verifie len de home et que = soit la*/
			return (env[i] + len + 1); /* env[i] = HOME=..., + len = '=', +1 = '/home/maeva' */
		i++;
	}
	return (NULL);
}

static char	**add_env(char **env, char *key, char *value, int i)
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

char	**set_env(char **env, char *key, char *value)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(key);
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0
			&& env[i][len] == '=')
		{
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
		i++;
	}
	return (add_env(env, key, value, i));
}

int	ft_cd(char **args, char **env)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (!args[1])
		path = get_env(env, "HOME");
	else
		path = args[1];
	if (!path)
	{
		printf("HOME not set\n");
		return (1);
	}
	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(old_pwd);
		return (1);
	}
	new_pwd = getcwd(NULL, 0);
	env = set_env(env, "OLDPWD", old_pwd);
	env = set_env(env, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
