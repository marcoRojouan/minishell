/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 11:45:37 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/15 13:53:10 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	handle_quotes(char *elem, char *res, t_idx *ctx,
	t_quote *quote)
{
	if (elem[ctx->i] == '\'' && !quote->in_double)
	{
		quote->in_single = !quote->in_single;
		res[ctx->j++] = elem[ctx->i++];
		return (1);
	}
	if (elem[ctx->i] == '"' && !quote->in_single)
	{
		quote->in_double = !quote->in_double;
		res[ctx->j++] = elem[ctx->i++];
		return (1);
	}
	return (0);
}

static void	expand_loop(char *elem, char *res, t_shell *shell)
{
	t_idx	ctx;
	t_quote	quote;

	ctx.i = 0;
	ctx.j = 0;
	quote.in_single = 0;
	quote.in_double = 0;
	while (elem[ctx.i])
	{
		if (handle_quotes(elem, res, &ctx, &quote))
			continue ;
		else if (elem[ctx.i] == '$' && !quote.in_single
			&& elem[ctx.i + 1] == '?')
			expand_status(res, &ctx, shell);
		else if (elem[ctx.i] == '$' && !quote.in_single
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
