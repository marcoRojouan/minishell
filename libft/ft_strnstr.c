/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 17:59:58 by mrojouan          #+#    #+#             */
/*   Updated: 2025/10/23 12:04:20 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (to_find[0] == '\0')
		return ((char *)str);
	while (i < n && str[i])
	{
		while (str[i + j] == to_find[j] && str[i + j] && i + j < n)
		{
			j++;
			if (to_find[j] == '\0')
				return ((char *)str + i);
		}
		i++;
		j = 0;
	}
	return (NULL);
}
