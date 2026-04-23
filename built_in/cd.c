/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 16:30:37 by malavaud          #+#    #+#             */
/*   Updated: 2026/04/23 22:54:00 by marvin           ###   ########.fr       */
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

/*fonction pour modifier la variable*/

int	ft_cd(char **args, char **env)
{
	char	*path;
	char	*old_pwd;
	char	*new_pwd;

	if (args[1])
		path = get_env(env, "HOME");
	else
		path = args[1];
	old_pwd = getcwd(NULL, 0);
}