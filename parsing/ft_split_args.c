/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:43:59 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/24 15:00:57 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
		if (!white_space(str[i]) &&
			(i == 0 || (white_space(str[i - 1]) && !in_quotes)))
			count++;
		if (str[i] == '"' || str[i] == '\'')
			in_quotes = !in_quotes;
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
		if (str[i] == '"' || str[i] == '\'')
			in_quotes = !in_quotes;
		else if (white_space(str[i]) && !in_quotes)
			break ;
		i++;
	}
	return (i);
}

static char *duplicate_wrd(char *str)
{
    char    *dup;
    int     len;

    len = word_len(str);
    dup = malloc(len + 1);
    if (!dup)
        return (NULL);
    ft_strlcpy(dup, str, len + 1);
    return (dup);
}

static void	skip_word(char *str, int *i)
{
	int	in_quotes;

	in_quotes = 0;
	while (str[*i])
	{
		if (str[*i] == '"' || str[*i] == '\'')
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
		/* inclure expand ici et les parametres necessaires */
		j++;
		skip_word(str, &i);
	}
	tab[j] = 0;
	return (1);
}

char	**ft_split_args(char *str)
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