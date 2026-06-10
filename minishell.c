/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:20:33 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/10 11:22:52 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*prompt_making(void)
{
	char	*cwd;
	char	*tmp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	tmp = ft_strjoin(cwd, " >");
	free(cwd);
	if (!tmp)
		return (NULL);
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	if (!prompt)
		return (NULL);
	return (prompt);
}

static int	init_shell(t_shell *shell, char **envp)
{
	shell->cmds = NULL;
	shell->env = copy_env(envp);
	shell->exit_status = 0;
	shell->cmd_count = 0;
	return (0);
}

static void	process_line(char *line, t_shell *shell)
{
	add_history(line);
	if (g_signal != 0)
		update_status(shell);
	signal(SIGINT, SIG_IGN);
	if (!parsing(line, shell))
	{
		free_cmds(shell);
		return ;
	}
	execution(shell);
	free_cmds(shell);
}

static int	shell_loop(t_shell *shell)
{
	char	*prompt;
	char	*line;

	while (1)
	{
		init_signals();
		prompt = prompt_making();
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			write(1, "exit\n", 5);
			return (0);
		}
		if (*line)
			process_line(line, shell);
		free(line);
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	(void)ac;
	(void)av;
	ft_bzero(&shell, sizeof(t_shell));
	init_shell(&shell, envp);
	shell_loop(&shell);
	ft_free_tab(shell.env);
	return (0);
}
