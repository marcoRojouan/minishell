/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/13 20:54:44 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/15 14:18:29 by mrojouan         ###   ########.fr       */
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

static void	replace_str(char **str)
{
	char	*tmp;

	tmp = remove_quotes(*str);
	free(*str);
	*str = tmp;
}

static void	remove_quotes_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		replace_str(&args[i]);
		i++;
	}
}

void	remove_quotes_cmds(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (shell->cmds[i]->args)
			remove_quotes_args(shell->cmds[i]->args);
		if (shell->cmds[i]->infile)
			replace_str(&shell->cmds[i]->infile);
		if (shell->cmds[i]->outfile)
			replace_str(&shell->cmds[i]->outfile);
		if (shell->cmds[i]->delimiter)
			replace_str(&shell->cmds[i]->delimiter);
		i++;
	}
}
