/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:36:58 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/27 16:52:36 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned char	*tmp;

	if (nmemb != 0 && nmemb * size / nmemb != size)
		return (NULL);
	if (!nmemb || !size)
		return (malloc(0));
	tmp = NULL;
	tmp = malloc(nmemb * size);
	if (!tmp)
		return (0);
	ft_bzero(tmp, nmemb * size);
	return (tmp);
}
