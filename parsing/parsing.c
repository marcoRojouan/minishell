/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:53:02 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/13 21:03:07 by mrojouan         ###   ########.fr       */
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

	if (!is_quote_closed(line))
	{
		ft_putstr_fd("minishell : parsing error\n", 2);
		return (0);
	}
	split_line = ft_split_args(line, shell);
	if (!split_line)
		return (0);
	if (!is_in_order(split_line))
	{
		ft_putstr_fd("minishell : syntax error\n", 2);
		ft_free_tab(split_line);
		return (0);
	}
	shell->cmd_count = count_cmds(split_line);
	shell->cmds = malloc(sizeof(t_cmd *) * (shell->cmd_count + 1));
	if (!shell->cmds)
		return (0);
	sort_line(split_line, shell);
	remove_quotes_cmds(shell);
	ft_free_tab(split_line);
	return (1);
}
