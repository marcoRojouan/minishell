/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils_bis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/10 20:38:57 by loup              #+#    #+#             */
/*   Updated: 2026/06/12 11:32:52 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	display_var(t_export var)
{
	if (var.value)
		printf("declare -x %s=\"%s\"\n", var.key, var.value);
	else
		printf("declare -x %s\n", var.key);
}

void	display_export(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->export_count)
	{
		display_var(shell->export_env[i]);
		i++;
	}
}

void	free_export_env(t_shell *shell)
{
	int	i;

	if (!shell->export_env)
		return ;
	i = 0;
	while (i < shell->export_count)
	{
		free(shell->export_env[i].key);
		free(shell->export_env[i].value);
		i++;
	}
	free(shell->export_env);
	shell->export_env = NULL;
	shell->export_count = 0;
}

int	find_export(t_shell *shell, char *key)
{
	int	i;

	i = 0;
	while (i < shell->export_count)
	{
		if (!ft_strcmp(shell->export_env[i].key, key))
			return (i);
		i++;
	}
	return (-1);
}

void	add_export_only(t_shell *shell, char *key)
{
	t_export	*new;
	int			i;

	if (find_export(shell, key) != -1)
		return ;
	new = malloc(sizeof(t_export) * (shell->export_count + 1));
	if (!new)
		return ;
	i = 0;
	while (i < shell->export_count)
	{
		new[i] = shell->export_env[i];
		i++;
	}
	new[i].key = ft_strdup(key);
	new[i].value = NULL;
	free(shell->export_env);
	shell->export_env = new;
	shell->export_count++;
}
