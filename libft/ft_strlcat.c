/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:07:20 by mrojouan          #+#    #+#             */
/*   Updated: 2025/10/23 11:52:02 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	l_len;
	size_t	index;

	l_len = 0;
	dest_len = 0;
	if (!dst && size == 0)
		return (ft_strlen(src));
	while (dst[dest_len] && dest_len < size)
		dest_len++;
	while (src[l_len])
		l_len++;
	index = 0;
	while (src[index] && (dest_len + index + 1) < size)
	{
		dst[dest_len + index] = src[index];
		index++;
	}
	if (dest_len < size)
		dst[dest_len + index] = '\0';
	return (dest_len + l_len);
}
