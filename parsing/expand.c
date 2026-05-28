/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:45:37 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/27 16:29:25 by malavaud         ###   ########.fr       */
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
			handle_quotes(elem, &ctx, &in_single, &in_double);
		else if (elem[ctx.i] == '"' && !in_single)
			handle_quotes(elem, &ctx, &in_single, &in_double);
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
	char	*res;

	res = malloc(2048);
	if (!res)
		return (NULL);
	expand_loop(elem, res, shell);
	return (res);
}
