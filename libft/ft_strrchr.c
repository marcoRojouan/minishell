/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:34:26 by mrojouan          #+#    #+#             */
/*   Updated: 2025/10/17 12:56:42 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int occ)
{
	int	len;

	len = ft_strlen(str);
	if ((unsigned char)occ == '\0')
		return ((char *)&str[len]);
	while (len > 0)
	{
		if (str[len - 1] == (unsigned char)occ)
			return ((char *)&str[len - 1]);
		len--;
	}
	return (NULL);
}
