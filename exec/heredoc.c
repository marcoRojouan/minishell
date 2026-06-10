/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/28 12:04:49 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/10 10:43:40 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	heredoc_child(t_shell *shell, int *pipefd, int i)
{
	char	*line;

	signal(SIGINT, heredoc_sigint);
	signal(SIGQUIT, SIG_IGN);
	close(pipefd[0]);
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (!ft_strcmp(line, shell->cmds[i]->delimiter))
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
	}
	close(pipefd[1]);
	free_cmds(shell);
	ft_free_tab(shell->env);
	if (signal_g == SIGINT)
		exit(130);
	exit(0);
}

static int	heredoc_parent(t_shell *shell, int *pipefd, pid_t pid, int i)
{
	int	status;

	close(pipefd[1]);
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		close(pipefd[0]);
		shell->exit_status = 130;
		signal_g = SIGINT;
		return (0);
	}
	shell->cmds[i]->fd_heredoc = pipefd[0];
	return (1);
}

static int	run_heredoc(t_shell *shell, int i)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		return (0);
	pid = fork();
	if (pid == 0)
		heredoc_child(shell, pipefd, i);
	return (heredoc_parent(shell, pipefd, pid, i));
}

int	prepare_heredoc(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->cmd_count)
	{
		if (shell->cmds[i]->delimiter)
		{
			if (!run_heredoc(shell, i))
				return (0);
		}
		i++;
	}
	return (1);
}
