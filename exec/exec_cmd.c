/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 14:05:10 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/28 17:01:55 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//void    handle_heredoc(t_cmd *cmd)
//{
//	// lit les lignes jusqu'au délimiteur
//	// écrit dans un pipe
//	// dup2 le read end sur stdin
//}

// c la Maeva

// tu prend la commande et le shell et
// tu l' execute avec execve mais d'abord il faut trouver le chemin de la commande.
// voila
// hesite pas a me demander si t'as besoin d'aide

//surtout pour les infile outfile et tout

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	if (!cmd->args || !cmd->args[0])
		exit(1);
	
	//ici on peut choisir entre un builtin (exec_child_builtin)
	//ou bien continuer avec findpath et execve si ca n'est pas un builtin
	if (exec_child_builtin(cmd, shell))
		exit(0); 
		
	path = find_path(cmd->args[0], shell->env);
	if (!path)
	{
		printf("%s: command not found\n", cmd->args[0]);
		exit(127);
	}
	execve(path, cmd->args, shell->env);
	perror("execve");
	free(path);
	exit (1);
	// appelle setup_redirections
	// cherche le path
	// appelle execve
}
