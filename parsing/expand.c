/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:45:37 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/13 20:52:27 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	expand_loop(char *elem, char *res, t_shell *shell)
{
	t_idx	ctx;
	int		in_single;
	int		in_double;

	ctx.i = 0;
	ctx.j = 0;
	in_single = 0;
	in_double = 0;
	while (elem[ctx.i])
	{
		if (elem[ctx.i] == '\'' && !in_double)
		{
			in_single = !in_single;
			res[ctx.j++] = elem[ctx.i++];
		}
		else if (elem[ctx.i] == '"' && !in_single)
		{
			in_double = !in_double;
			res[ctx.j++] = elem[ctx.i++];
		}
		else if (elem[ctx.i] == '$' && !in_single && elem[ctx.i + 1] == '?')
			expand_status(res, &ctx, shell);
		else if (elem[ctx.i] == '$' && !in_single
			&& (ft_isalnum(elem[ctx.i + 1])
				|| elem[ctx.i + 1] == '_'))
			expand_var(elem, res, &ctx, shell);
		else
			res[ctx.j++] = elem[ctx.i++];
	}
	res[ctx.j] = '\0';
}

char	*expand(char *elem, t_shell *shell)
{
	char	*tmp;
	char	*res;

	tmp = malloc(64000);
	if (!tmp)
		return (NULL);
	expand_loop(elem, tmp, shell);
	res = ft_strdup(tmp);
	if (!res)
	{
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (res);
}
