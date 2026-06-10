/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 11:53:20 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/10 20:33:39 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	count_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

static int	fill_export(t_export *export, char *env_line)
{
	char	*equal;

	equal = ft_strchr(env_line, '=');
	if (!equal)
		return (0);
	export->key = ft_substr(env_line, 0, equal - env_line);
	if (!export->key)
		return (0);
	export->value = ft_strdup(equal + 1);
	if (!export->value)
	{
		free(export->key);
		return (0);
	}
	return (1);
}

int	init_export_env(t_shell *shell)
{
	int	i;

	shell->export_count = count_env(shell->env);
	shell->export_env = malloc(sizeof(t_export)
			* shell->export_count);
	if (!shell->export_env)
		return (0);
	i = 0;
	while (i < shell->export_count)
	{
		if (!fill_export(&shell->export_env[i],
				shell->env[i]))
			return (0);
		i++;
	}
	return (1);
}

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

int	check_key(char *key)
{
	if (!valid_key(key))
	{
		printf("export: `%s': not a valid identifier\n", key);
		return (0);
	}
	return (1);
}
