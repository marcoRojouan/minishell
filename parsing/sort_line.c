/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:14:46 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/28 15:04:54 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	pipe_handler(t_shell *shell, int *j, int *k)
{
	(*j)++;
	shell->cmds[*j] = malloc(sizeof(t_cmd));
	if (!shell->cmds[*j])
		return ;
	ft_bzero(shell->cmds[*j], sizeof(t_cmd));
	*k = 0;
}

static int  args_handler(char **split_line, t_shell *shell, int i, int j, int *k)
{
    int arg_count;

    arg_count = 0;
    while (split_line[i + arg_count] && is_word(split_line[i + arg_count]))
        arg_count++;
    shell->cmds[j]->args = malloc(sizeof(char *) * (arg_count + 1));
    if (!shell->cmds[j]->args)
        return (0);
    while (split_line[i] && is_word(split_line[i]))
    {
        shell->cmds[j]->args[*k] = ft_strdup(split_line[i]);
        (*k)++;
        i++;
    }
    shell->cmds[j]->args[*k] = NULL;
    return (arg_count);
}

static void	redirect_handler(char **split_line, t_shell *shell, int *i, int j)
{
	if (!ft_strcmp(split_line[*i], "<<"))
	{
		++(*i);
		shell->cmds[j]->delimiter = split_line[*i];
	}
	else if (!ft_strcmp(split_line[*i], ">>"))
	{
		++(*i);
		shell->cmds[j]->insert = 1;
		shell->cmds[j]->outfile = split_line[*i];
	}
	else if (!ft_strcmp(split_line[*i], "<"))
	{
		++(*i);
		shell->cmds[j]->infile = split_line[*i];
	}
	else if (!ft_strcmp(split_line[*i], ">"))
	{
		++(*i);
		shell->cmds[j]->outfile = split_line[*i];
	}
}

void	sort_line(char **split_line, t_shell *shell)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	shell->cmds[j] = malloc(sizeof(t_cmd));
	if (!shell->cmds[j])
		return ;
	ft_bzero(shell->cmds[j], sizeof(t_cmd));
	while (split_line[i])
	{
		if (!ft_strcmp(split_line[i], "|"))
        	pipe_handler(shell, &j, &k);
    	else if (is_word(split_line[i]))
        	i += args_handler(split_line, shell, i, j, &k) - 1;
    	else
        	redirect_handler(split_line, shell, &i, j);
    	i++;
	}
}
