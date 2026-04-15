/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 12:53:13 by mrojouan          #+#    #+#             */
/*   Updated: 2025/10/17 11:58:16 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*duplicata;
	int		i;
	int		len;

	len = ft_strlen(s);
	duplicata = NULL;
	duplicata = malloc(sizeof(char) * len + 1);
	if (!duplicata)
		return (0);
	i = 0;
	while (i < len)
	{
		duplicata[i] = s[i];
		i++;
	}
	duplicata[i] = '\0';
	return (duplicata);
}
