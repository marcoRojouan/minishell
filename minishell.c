/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:20:33 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/09 13:50:31 by mrojouan         ###   ########.fr       */
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
		return NULL;
	tmp = ft_strjoin(cwd, " >");
	free(cwd);
	if (!tmp)
		return NULL;
	prompt = ft_strjoin(tmp, "$ ");
	free(tmp);
	if (!prompt)
		return NULL;
	return (prompt);
}

char	**copy_env(char **envp)
{
	int		i;
	char	**new_env;

	i = 0;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		if (!new_env[i])
		{
			while (i--)
				free(new_env[i]);
			free(new_env);
			return NULL;
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

static int	init_shell(t_shell *shell, char **envp)
{
	shell->cmds = NULL;
	shell->env = copy_env(envp);
	shell->exit_status = 0;
	shell->cmd_count = 0;
	return (0);
}

static void	update_status(t_shell *shell)
{
	shell->exit_status = signal_g;
	signal_g = 0;
}

int	main(int ac, char **av, char **envp)
{
	char        *prompt;
	char        *line;
	t_shell     shell;

	(void)ac;
	(void)av;
	ft_bzero(&shell, sizeof(t_shell));
	init_shell(&shell, envp);
	while (1)
	{
		init_signals();
		prompt = prompt_making();
		line = readline(prompt);
		free(prompt);
		if (!line)
		{
			write(1, "exit\n", 5);
			break ;
		}
		if (*line)
		{
			add_history(line);
			if (signal_g != 0)
				update_status(&shell);
			signal(SIGINT, SIG_IGN);
			if (!parsing(line, &shell))
			{
				free_cmds(&shell);
				continue ;
			}
			else
				execution(&shell);
			free_cmds(&shell);
		}
		free(line);
	}
	ft_free_tab(shell.env);
	return (0);
}
