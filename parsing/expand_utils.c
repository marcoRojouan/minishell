/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:09:11 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/15 13:53:04 by malavaud         ###   ########.fr       */
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

void	handle_quotes(char *elem, char *res, t_idx *ctx, t_quote *quote)
{
	res[ctx->j++] = elem[ctx->i];
	if (elem[ctx->i] == '\'' && !quote->in_double)
		quote->in_single = !quote->in_single;
	else if (elem[ctx->i] == '"' && !quote->in_single)
		quote->in_double = !quote->in_double;
	ctx->i++;
}

void	expand_var(char *elem, char *res, t_idx *ctx, t_shell *shell)
{
	char	*value;
	int		var_start;

	ctx->i++;
	var_start = ctx->i;
	while (elem[ctx->i] && (ft_isalnum(elem[ctx->i]) || elem[ctx->i] == '_'))
		ctx->i++;
	value = get_var_value(elem + var_start, ctx->i - var_start, shell->env);
	while (value && *value)
		res[ctx->j++] = *value++;
}

void	expand_status(char *res, t_idx *ctx, t_shell *shell)
{
	char	*status;
	int		k;

	k = 0;
	status = ft_itoa(shell->exit_status);
	while (status[k])
	{
		res[ctx->j] = status[k];
		ctx->j++;
		k++;
	}
	ctx->i += 2;
	free(status);
}
