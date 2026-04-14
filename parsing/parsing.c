/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:53:02 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/14 14:15:19 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

/* FONCTION PRINCIPALE DE PARSING POUR RECEVOIR LA LIGNE */
int	parsing(char *line)
{
	if (!ft_isalnum(line[0]))
		return (0);
	return (1);
}
