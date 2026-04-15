
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 15:36:58 by mrojouan          #+#    #+#             */
/*   Updated: 2025/10/23 17:36:48 by mrojouan         ###   ########.fr       */
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
