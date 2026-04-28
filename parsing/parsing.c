/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:53:02 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/28 12:06:00 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	
	split_line = ft_split_args(line, shell);
	if (!split_line)
		return (0);
	cmd_count = count_cmds(split_line);
	shell->cmds = malloc(sizeof(t_cmd) * (cmd_count + 1));
	if (!shell->cmds)
		return (0);
	sort_line(split_line, shell);
	//print_cmds(shell, cmd_count);
	return (1);
}
