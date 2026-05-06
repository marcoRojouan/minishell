/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:20:33 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/06 14:33:08 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*prompt_making(void)
{
	char	*cwd;
	char	*tmp;
	char	*prompt;

	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin(cwd, " >");
	prompt = ft_strjoin(tmp, "$ ");
	free(cwd);
	free(tmp);
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
			return (NULL);
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

int	main(int ac, char **av, char **envp)
{
	char		*prompt;
	char		*line;
	t_shell		shell;

	(void)ac;
	(void)av;
	init_shell(&shell, envp);
	while (1)
	{
		prompt = prompt_making();
		line = readline(prompt);
		if (!line)
			break ;
		if (*line)
		{
			add_history(line);
			if (!parsing(line, &shell))
				ft_putstr_fd("minishell : parsing error\n", 2);
			else if (shell.cmds[0]->args)
			{
				if (ft_strcmp(shell.cmds[0]->args[0], "pwd") == 0)
					ft_pwd();
				if (ft_strcmp(shell.cmds[0]->args[0], "env") == 0)
					ft_env(shell.env);
				if (ft_strcmp(shell.cmds[0]->args[0], "export") == 0)
					ft_export(shell.cmds[0]->args, &shell.env);
				if (ft_strcmp(shell.cmds[0]->args[0], "unset") == 0)
					ft_unset(shell.cmds[0]->args, &shell.env);
				if (ft_strcmp(shell.cmds[0]->args[0], "echo") == 0)
					ft_echo(shell.cmds[0]->args);
				if (ft_strcmp(shell.cmds[0]->args[0], "cd") == 0)
					ft_cd(shell.cmds[0]->args, shell.env);
			}
		}
		free(line);
	}
}
