/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_space.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: loup <loup@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:43:59 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/21 18:47:41 by loup             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
	int	in_quotes;

	i = 0;
	count = 0;
	in_quotes = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] == '"')
			in_quotes = !in_quotes;
		if (!white_space(str[i]) &&
			(i == 0 || (white_space(str[i - 1]) && !in_quotes)))
			count++;
		i++;
	}
	return (count);
}

static int	word_len(char *str)
{
	int	i;
	int	in_quotes;

	i = 0;
	in_quotes = 0;
	while (str[i])
	{
		if (str[i] == '"')
			in_quotes = !in_quotes;
		else if (white_space(str[i]) && !in_quotes)
			break ;
		i++;
	}
	return (i);
}

static char	*duplicate_wrd(char *str)
{
	char	*dup;
	int		i;
	int		j;
	int		in_quotes;

	i = 0;
	j = 0;
	in_quotes = 0;
	dup = malloc(word_len(str) + 1);
	if (!dup)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '"')
			in_quotes = !in_quotes;
		else if (white_space(str[i]) && !in_quotes)
			break ;
		else
			dup[j++] = str[i];
		i++;
	}
	dup[j] = '\0';
	return (dup);
}

static void	skip_word(char *str, int *i)
{
	int	in_quotes;

	in_quotes = 0;
	while (str[*i])
	{
		if (str[*i] == '"')
			in_quotes = !in_quotes;
		else if (!in_quotes && white_space(str[*i]))
			break ;
		(*i)++;
	}
}

static int	fill_tab(char *str, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && white_space(str[i]))
			i++;
		if (!str[i])
			break ;
		tab[j] = duplicate_wrd(str + i);
		if (!tab[j])
		{
			ft_free_tab(tab);
			return (0);
		}
		j++;
		skip_word(str, &i);
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