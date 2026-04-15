/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:47:39 by mrojouan          #+#    #+#             */
/*   Updated: 2025/10/20 12:47:00 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	slen;

	if (!s)
		return (0);
	slen = ft_strlen(s);
	if (len > slen - start)
		len = slen - start;
	if (start > slen)
	{
		str = ft_strdup("");
		return (str);
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (0);
	i = 0;
	while (i < len && s[start + i])
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
