/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:43:59 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/27 15:50:01 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*duplicate_wrd(char *str)
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

static int	process_word(char *str, char **tab, int *i, int j, t_shell *shell)
{
	tab[j] = duplicate_wrd(str + *i);
	if (!tab[j])
		return (0);
	tab[j] = expand(tab[j], shell);
	if (!tab[j])
		return (0);
	skip_word(str, i);
	return (1);
}

static int	fill_tab(char *str, char **tab, t_shell *shell)
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
		if (!process_word(str, tab, &i, j, shell))
		{
			ft_free_tab(tab);
			return (0);
		}
		j++;
	}
	tab[j] = 0;
	return (1);
}

char	**ft_split_args(char *str, t_shell *shell)
{
	char	**tab;
	int		word_count;

	word_count = count_words(str);
	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * (word_count + 1));
	if (!tab)
		return (NULL);
	if (!fill_tab(str, tab, shell))
		return (0);
	return (tab);
}