/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:53:02 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/14 13:59:41 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* FONCTION PRINCIPALE DE PARSING POUR RECEVOIR LA LIGNE */
int parsing(char *line)
{
	if (!ft_isalnum(line[0]))
		return (0);
	return (1);
}