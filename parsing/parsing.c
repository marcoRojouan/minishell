/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:53:02 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/15 14:42:27 by malavaud         ###   ########.fr       */
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
	
	split_line = ft_split_space(line);
	if (!split_line)
		return (0);
	cmd_count = count_cmds(split_line);
	shell->cmds = malloc(sizeof(t_cmd) * cmd_count);
	if (!shell->cmds)
		return (0);
	return (1);
}
