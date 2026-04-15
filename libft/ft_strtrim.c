/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:49:50 by mrojouan          #+#    #+#             */
/*   Updated: 2025/10/18 12:39:17 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isset(char const *set, char const s1char)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s1char)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*trimstr;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_isset(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_isset(set, s1[end - 1]))
		end--;
	len = end - start;
	trimstr = (char *)malloc(sizeof(char) * (len + 1));
	if (!trimstr)
		return (NULL);
	ft_strlcpy(trimstr, s1 + start, len + 1);
	return (trimstr);
}
