/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_line_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 17:00:53 by malavaud          #+#    #+#             */
/*   Updated: 2026/06/15 17:04:11 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	handle_output_redirect(t_context *ctx, char **split_line,
		t_shell *shell)
{
	if (!ft_strcmp(split_line[ctx->i], ">>"))
		shell->cmds[ctx->j]->insert = 1;
	if (shell->cmds[ctx->j]->outfile)
		free(shell->cmds[ctx->j]->outfile);
	shell->cmds[ctx->j]->outfile = ft_strdup(split_line[++ctx->i]);
	if (!shell->cmds[ctx->j]->outfile)
		return (0);
	return (1);
}
