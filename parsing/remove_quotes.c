/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:54:44 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/13 21:00:25 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*remove_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		in_single;
	int		in_double;

	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	remove_quotes_cmds(t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (shell->cmds[i]->args)
		{
			j = 0;
			while (shell->cmds[i]->args[j])
			{
				tmp = remove_quotes(shell->cmds[i]->args[j]);
				free(shell->cmds[i]->args[j]);
				shell->cmds[i]->args[j] = tmp;
				j++;
			}
		}
		if (shell->cmds[i]->infile)
		{
			tmp = remove_quotes(shell->cmds[i]->infile);
			free(shell->cmds[i]->infile);
			shell->cmds[i]->infile = tmp;
		}
		if (shell->cmds[i]->outfile)
		{
			tmp = remove_quotes(shell->cmds[i]->outfile);
			free(shell->cmds[i]->outfile);
			shell->cmds[i]->outfile = tmp;
		}
		if (shell->cmds[i]->delimiter)
		{
			tmp = remove_quotes(shell->cmds[i]->delimiter);
			free(shell->cmds[i]->delimiter);
			shell->cmds[i]->delimiter = tmp;
		}
		i++;
	}
}
