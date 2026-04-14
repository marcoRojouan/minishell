/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:20:33 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/14 14:37:28 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*prompt_making()
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

/* FONCTION D'INITIALISATION DE STRUCTURE */

static int	init_shell(t_shell *shell, char **envp)
{
	shell->env = envp;
	shell->exit_status = 0;
}

int	main(int ac, char **av, char **envp)
{
	char	*prompt;
	char	*line;
	t_shell	*shell;

	(void)ac;
	(void)av;
	init_shell(&shell, envp);
	while (1)
	{
		prompt = prompt_making(); /* on cree notre ligne fixe "minishell >$"*/
		line = readline(prompt); /* on affiche la ligne fixe et on attend une commande*/
		free(prompt);
		// if (*line)
		// 	add_history(line); /* on ajoute la ligne a notre historique de ligne */
		if (parsing(line))
			printf("%s\n", line);/* si la ligne existe on printf son contenu */		
	}
}
