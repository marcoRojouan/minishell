/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 10:48:48 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/15 13:52:05 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	update_export(t_shell *shell, char *key, char *value)
{
	int	i;

	i = find_export(shell, key);
	if (i == -1)
	{
		add_export_only(shell, key);
		i = shell->export_count - 1;
	}
	free(shell->export_env[i].value);
	shell->export_env[i].value = ft_strdup(value);
}

static char	**handle_assignment(char *arg, t_shell *shell, char *ptr)
{
	char	*key;
	char	*value;

	key = ft_substr(arg, 0, ptr - arg);
	value = ptr + 1;
	if (!check_key(key))
		return (free(key), shell->env);
	update_export(shell, key, value);
	shell->env = set_env(shell->env, key, value);
	free(key);
	return (shell->env);
}

static char	**handle_plus(char *arg, t_shell *shell)
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
		return (free(key), shell->env);
	old = get_env(shell->env, key);
	if (old)
	{
		tmp = ft_strjoin(old, value);
		update_export(shell, key, tmp);
		shell->env = set_env(shell->env, key, tmp);
		free(tmp);
	}
	else
		shell->env = set_env(shell->env, key, value);
	free(key);
	return (shell->env);
}

static char	**export_one_arg(char *arg, t_shell *shell)
{
	char	*ptr;

	if (ft_strnstr(arg, "+=", ft_strlen(arg)))
		return (handle_plus(arg, shell));
	ptr = ft_strchr(arg, '=');
	if (ptr)
		return (handle_assignment(arg, shell, ptr));
	if (!check_key(arg))
		return (shell->env);
	add_export_only(shell, arg);
	return (shell->env);
}

char	**ft_export(char **args, t_shell *shell)
{
	int	i;

	if (!args[1])
	{
		display_export(shell);
		return (shell->env);
	}
	i = 1;
	while (args[i])
	{
		shell->env = export_one_arg(args[i], shell);
		i++;
	}
	return (shell->env);
}
