/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:30:37 by malavaud          #+#    #+#             */
/*   Updated: 2026/04/24 15:08:51 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
PWD = le dossier actuel,  variable d'enviroonement
PATH = la liste des chemins,  trouver les commandes
ENV = environnement du programme, KEY=VALUE, mémoire du shell
HOME = dossier personnel
OLDPWD = ancienr dossier
*/

static char	*get_env(char **env, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(key); /*le home etc*/
	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')/*verifie len de home et que = soit la*/
			return (env[i] + len + 1); /* env[i] = HOME=..., + len = '=', +1 = '/home/maeva' */
		i++;
	}
	return (NULL);
}

static void	set_env(char **env, char *key, char *value)
{
	int		i;
	int		len;
	char	*new;

	i = 0;
	len = ft_strlen(key);

	while (env[i])
	{
		if (ft_strncmp(env[i], key, len) == 0 && env[i][len] == '=')
		{
			new = malloc(len + ft_strlen(value) + 2);
			if (!new)
				return ;
			strcpy(new, key);
			strcat(new, "=");
			strcat(new, value);
			env[i] = new;
			return ;
		}
		i++;
	}
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
	set_env(env, "OLDPWD", old_pwd);
	set_env(env, "PWD", new_pwd);
	free(old_pwd);
	free(new_pwd);
	return (0);
}
