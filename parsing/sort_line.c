/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:14:46 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/08 11:20:07 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipe_handler(t_context *ctx, t_shell *shell)
{
	(ctx->j)++;
	shell->cmds[ctx->j] = malloc(sizeof(t_cmd));
	if (!shell->cmds[ctx->j])
		return ;
	ft_bzero(shell->cmds[ctx->j], sizeof(t_cmd));
	shell->cmds[ctx->j]->fd_heredoc = -1;
	ctx->k = 0;
}

static int	args_handler(t_context *ctx, char **split_line, t_shell *shell)
{
	int	arg_count;

	arg_count = 0;
	while (split_line[ctx->i + arg_count]
		&& is_word(split_line[ctx->i + arg_count]))
		arg_count++;
	shell->cmds[ctx->j]->args = malloc(sizeof(char *) * (arg_count + 1));
	if (!shell->cmds[ctx->j]->args)
		return (0);
	while (split_line[ctx->i] && is_word(split_line[ctx->i]))
	{
		shell->cmds[ctx->j]->args[ctx->k] = ft_strdup(split_line[ctx->i]);
		ctx->k++;
		ctx->i++;
	}
	shell->cmds[ctx->j]->args[ctx->k] = NULL;
	return (arg_count);
}

static int    redirect_handler(t_context *ctx, char **split_line, t_shell *shell)
{
	if (!split_line[ctx->i + 1])
		return (0);
	if (!ft_strcmp(split_line[ctx->i], "<<"))
	{
		shell->cmds[ctx->j]->delimiter = ft_strdup(split_line[++ctx->i]);
		if (!shell->cmds[ctx->j]->delimiter)
			return (0);
	}
	else if (!ft_strcmp(split_line[ctx->i], ">>") 
				|| !ft_strcmp(split_line[ctx->i], ">"))
	{
		if (!ft_strcmp(split_line[ctx->i], ">>"))
			shell->cmds[ctx->j]->insert = 1;
		shell->cmds[ctx->j]->outfile = ft_strdup(split_line[++ctx->i]);
		if (!shell->cmds[ctx->j]->outfile)
			return (0);
	}
	else if (!ft_strcmp(split_line[ctx->i], "<"))
	{
		shell->cmds[ctx->j]->infile = ft_strdup(split_line[++ctx->i]);
		if (!shell->cmds[ctx->j]->infile)
			return (0);
	}
	return (1);
}

void	sort_line(char **split_line, t_shell *shell)
{
	t_context	ctx;

	ctx.i = 0;
	ctx.j = 0;
	ctx.k = 0;
	shell->cmds[0] = malloc(sizeof(t_cmd));
	if (!shell->cmds[0])
		return ;
	ft_bzero(shell->cmds[0], sizeof(t_cmd));
	shell->cmds[0]->fd_heredoc = -1;
	while (split_line[ctx.i])
	{
		if (!ft_strcmp(split_line[ctx.i], "|"))
			pipe_handler(&ctx, shell);
		else if (is_word(split_line[ctx.i]))
		{
			args_handler(&ctx, split_line, shell);
			ctx.i--;
		}
		else
			redirect_handler(&ctx, split_line, shell);
		ctx.i++;
	}
}
