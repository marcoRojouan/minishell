/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:43:59 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/15 12:05:20 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

static int	count_words(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (!str || !str[0])
		return (0);
	if (!white_space(str[0]))
	{
		count += 1;
	}
	i++;
	while (str[i])
	{
		if (!white_space(str[i]) && white_space(str[i - 1]))
			count++;
		i++;
	}
	return (count);
}

static char	*duplicate_wrd(char *str)
{
	char	*dup;
	int		word_len;
	int		i;

	word_len = 0;
	while (!white_space(str[word_len]) && str[word_len])
		word_len++;
	if (!str)
		return (NULL);
	dup = malloc(sizeof(char) * (word_len + 1));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < word_len)
	{
		dup[i] = str[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

static int	fill_tab(char *str, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((i == 0 && !white_space(str[i]))
			|| (i > 0 && !white_space(str[i]) && white_space(str[i - 1])))
		{
			tab[j] = duplicate_wrd(str + i);
			if (!tab[j])
			{
				ft_free_tab(tab);
				return (0);
			}
			j++;
		}
		i++;
	}
	tab[j] = 0;
	return (1);
}

char	**ft_split_space(char *str)
{
	char	**tab;
	int		word_count;

	word_count = count_words(str);
	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * (word_count + 1));
	if (!tab)
		return (NULL);
	if (!fill_tab(str, tab))
		return (0);
	return (tab);
}
