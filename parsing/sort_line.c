/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:14:46 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/05 15:29:49 by mrojouan         ###   ########.fr       */
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
	ctx->k = 0;
}

static int  args_handler(t_context *ctx, char **split_line, t_shell *shell)
{
    int arg_count;

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

static void	redirect_handler(t_context *ctx, char **split_line, t_shell *shell)
{
	if (!ft_strcmp(split_line[ctx->i], "<<"))
	{
		ctx->i++;
		shell->cmds[ctx->j]->delimiter = split_line[ctx->i];
	}
	else if (!ft_strcmp(split_line[ctx->i], ">>"))
	{
		ctx->i++;
		shell->cmds[ctx->j]->insert = 1;
		shell->cmds[ctx->j]->outfile = split_line[ctx->i];
	}
	else if (!ft_strcmp(split_line[ctx->i], "<"))
	{
		ctx->i++;
		shell->cmds[ctx->j]->infile = split_line[ctx->i];
	}
	else if (!ft_strcmp(split_line[ctx->i], ">"))
	{
		ctx->i++;
		shell->cmds[ctx->j]->outfile = split_line[ctx->i];
	}
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
