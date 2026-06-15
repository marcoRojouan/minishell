/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 13:51:32 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/15 13:51:35 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	**update_pwd(char **env, char *old_pwd)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (old_pwd)
		env = set_env(env, "OLDPWD", old_pwd);
	if (new_pwd)
	{
		env = set_env(env, "PWD", new_pwd);
		free(new_pwd);
	}
	return (env);
}

static char	*get_cd_path(char **args, char **env, int *need_free)
{
	char	*home;
	char	*path;

	if (!args[1] || !ft_strcmp(args[1], "~"))
		path = get_env(env, "HOME");
	else if (!ft_strcmp(args[1], "-"))
	{
		path = get_env(env, "OLDPWD");
		if (path)
			printf("%s\n", path);
	}
	else if (args[1][0] == '~')
	{
		home = get_env(env, "HOME");
		if (!home)
			return (NULL);
		path = ft_strjoin(home, args[1] + 1);
		*need_free = 1;
	}
	else
		path = args[1];
	return (path);
}

static char	**change_directory(char **env, char *path, int need_free)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (chdir(path) != 0)
	{
		perror("cd");
		free(old_pwd);
		if (need_free)
			free(path);
		return (env);
	}
	env = update_pwd(env, old_pwd);
	free(old_pwd);
	if (need_free)
		free(path);
	return (env);
}

char	**ft_cd(char **args, char **env)
{
	char	*path;
	int		need_free;

	need_free = 0;
	if (args[1] && args[2])
	{
		printf("cd: too many arguments\n");
		return (env);
	}
	path = get_cd_path(args, env, &need_free);
	if (!path)
	{
		if (args[1] && !ft_strcmp(args[1], "-"))
			printf("cd: OLDPWD not set\n");
		else
			printf("cd: HOME not set\n");
		return (env);
	}
	return (change_directory(env, path, need_free));
}
