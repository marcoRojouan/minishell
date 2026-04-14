/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:20:33 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/14 14:14:59 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char *prompt_making()
{
	char *cwd;
	char *tmp;
	char *prompt;
	
	cwd = getcwd(NULL, 0);
	tmp = ft_strjoin(cwd, " >");
	prompt = ft_strjoin(tmp, "$ ");
	free(cwd);
	free(tmp);
	return (prompt);
}

/* FONCTION D'INITIALISATION DE STRUCTURE */

int main(int ac, char **av, char **envp)
{
	char *prompt;
	char *line;
	(void)ac;
	(void)av;
	(void)envp;
	
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
