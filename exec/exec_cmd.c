/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/25 14:05:10 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/26 16:28:49 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// c la Maeva

// tu prend la commande et le shell et
// tu l' execute avec execve mais d'abord il faut trouver le chemin de la commande.
// voila
// hesite pas a me demander si t'as besoin d'aide

//surtout pour les infile outfile et tout

void	exec_cmd(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = find_path(cmd->args[0], shell->shell);
}