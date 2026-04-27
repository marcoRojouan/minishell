/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:45:37 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/27 14:23:57 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	expand_loop(char *elem, char *res, t_shell *shell)
{
	int	i;
	int	j;
	int	in_single;
	int	in_double;

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (elem[i])
	{
		if (elem[i] == '\'' && !in_double)
			handle_quotes(elem, &i, &in_single, &in_double);
		else if (elem[i] == '"' && !in_single)
			handle_quotes(elem, &i, &in_single, &in_double);
		else if (elem[i] == '$' && !in_single && elem[i + 1] == '?')
			expand_status(res, &i, &j, shell);
		else if (elem[i] == '$' && !in_single && (ft_isalnum(elem[i + 1])
				|| elem[i + 1] == '_'))
			expand_var(elem, res, &i, &j, shell);
		else
			res[j++] = elem[i++];
	}
	res[j] = '\0';
}

char *expand(char *elem, t_shell *shell)
{
	char	*res;

	res = malloc(2048);
	if (!res)
		return (NULL);
	expand_loop(elem, res, shell);
	return (res);
}	
