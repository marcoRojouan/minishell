/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:38:13 by mrojouan          #+#    #+#             */
/*   Updated: 2025/10/23 11:33:32 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp_s;
	size_t			i;

	i = 0;
	tmp_s = (unsigned char *)s;
	if (n == 0)
		return (NULL);
	while (i < n)
	{
		if (tmp_s[i] == (unsigned char)c)
			return ((void *)&tmp_s[i]);
		i++;
	}
	return (NULL);
}
