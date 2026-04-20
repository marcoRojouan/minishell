/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:53:02 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/16 14:55:14 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
if (1er element du split == <)
	le +1 = infile
// if (1er element du split == <<)
// 	heredoc = 1;
shell->cmds[i]->args = {cat, -e}
if (split[i] == '|')
	on peut continuer et passer a la commande suivante
shell->cmds[i]->args = {grep, v}
if (split [i] == > ou >>)
	if (>>)
		insert = 1 
	le +1 = outfile
sinon c bon finito pipeau
*/



static int	count_cmds(char **split_line)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (split_line[i])
	{
		if (split_line[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

int	parsing(char *line, t_shell *shell)
{
	char	**split_line;
	int		cmd_count;
	
	split_line = ft_split_space(line);
	if (!split_line)
		return (0);
	cmd_count = count_cmds(split_line);
	shell->cmds = malloc(sizeof(t_cmd) * (cmd_count + 1));
	if (!shell->cmds)
		return (0);
	
	return (1);
}
