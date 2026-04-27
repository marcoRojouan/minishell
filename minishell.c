/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:20:33 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/27 16:49:37 by malavaud         ###   ########.fr       */
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
	while (envp[i]) /*compter les variables*/
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);/*copie du tableau*/
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
		prompt = prompt_making(); /* on cree notre ligne fixe "minishell >$"*/
		line = readline(prompt); /* on affiche la ligne fixe et on attend une commande*/
		free(prompt);
		if (*line)
			add_history(line); /* on ajoute la ligne a notre historique de ligne */
		if (!parsing(line, &shell))
			printf("problems");	
	}
}
