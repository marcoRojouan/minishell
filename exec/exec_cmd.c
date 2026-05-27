/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 14:05:10 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/27 11:03:03 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void    handle_heredoc(t_cmd *cmd)
{
    // lit les lignes jusqu'au délimiteur
    // écrit dans un pipe
    // dup2 le read end sur stdin
}

// c la Maeva

// tu prend la commande et le shell et
// tu l' execute avec execve mais d'abord il faut trouver le chemin de la commande.
// voila
// hesite pas a me demander si t'as besoin d'aide

//surtout pour les infile outfile et tout

void    exec_cmd(t_cmd *cmd, t_shell *shell)
{
    // appelle setup_redirections
    // cherche le path
    // appelle execve
}
