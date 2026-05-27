/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 11:39:26 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/27 16:32:53 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	find_path_index(char **envp, char *value)
{
	int	i;
	int	j;

	i = 0;
	while (envp[i])
	{
		j = 0;
		while (value[j] == envp[i][j] && (value[j] || envp[i][j]))
			j++;
		if (value[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}

static char	*join_path(char *dir, char *cmd)
{
	char	*tmp;
	char	*final;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	final = ft_strjoin(tmp, cmd);
	if (!final) /* peut etre free tmp avant*/
		return (NULL);
	free(tmp);
	return (final);
}

static char	**get_env_path(char *env_path)
{
	int		i;
	char	**paths;

	i = 0;
	while (env_path[i] != '=')
		i++;
	paths = ft_split(env_path + i, ':');
	if (!paths)
		return (NULL);
	return (paths);
}

static char	*find_path_in_dirs(char *cmd, char **paths)
{
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		path = join_path(paths[i], cmd);
		if (access(path, X_OK) == 0)
		{
			ft_free_tab(paths);
			return (path);
		}
		free(path);
		i++;
	}
	ft_free_tab(paths);
	return (NULL);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	int		path_index;
	char	*result;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (NULL);
	}
	path_index = find_path_index(envp, "PATH=");
	if (path_index == -1)
		return (NULL);
	paths = get_env_path(envp[path_index]);
	result = find_path_in_dirs(cmd, paths);
	return (result);
}
