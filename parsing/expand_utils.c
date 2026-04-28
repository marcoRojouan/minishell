/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:09:11 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/27 14:24:26 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*get_var_value(char *start, int len, char**env)
{
	char	*var_name;
	int		i;

	var_name = ft_substr(start, 0, len);
	if (!var_name)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], var_name, len) && env[i][len] == '=')
		{
			free(var_name);
			return (env[i] + len + 1);
		}
		i++;
	}
	free(var_name);
	return ("");
}

void	handle_quotes(char *elem, int *i, int *in_single, int *in_double)
{
	if (elem[*i] == '\'' && !(*in_double))
		*in_single = !(*in_single);
	else if (elem[*i] == '"' && !(*in_single))
		*in_double = !(*in_double);
	(*i)++;
}

void	expand_var(char *elem, char *res, int *i, int *j, t_shell *shell)
{
	char	*value;
	int		var_start;

	(*i)++;
	var_start = *i;
	while (elem[*i] && (ft_isalnum(elem[*i]) || elem[*i] == '_'))
		(*i)++;
	value = get_var_value(elem + var_start, *i - var_start, shell->env);
	while (value && *value)
		res[(*j)++] = *value++;
}

void	expand_status(char *res, int *i, int *j, t_shell *shell)
{
	char	*status;
	int		k;

	k = 0;
	status = ft_itoa(shell->exit_status);
	while (status[k])
	{
		res[(*j)] = status[k];
		j++;
		k++;
	}
	*i += 2;
}