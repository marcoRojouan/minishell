/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:04:49 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/08 11:55:52 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	prepare_heredoc(t_shell *shell)
{
	int		i;
	int		pipefd[2];
	char	*line;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (shell->cmds[i]->delimiter)
		{
			if (pipe(pipefd) == -1)
				return (0);
			while (1)
			{
				line = readline("> ");
				if (!line || !ft_strcmp(line, shell->cmds[i]->delimiter))
				{
					free(line);
					break ;
				}
				write(pipefd[1], line, ft_strlen(line));
				write(pipefd[1], "\n", 1);
				free(line);
			}
			close(pipefd[1]);
			shell->cmds[i]->fd_heredoc = pipefd[0];
		}
		i++;
	}
	return (1);
}
