/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 11:43:59 by mrojouan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/05/06 13:31:58 by malavaud         ###   ########.fr       */
=======
/*   Updated: 2026/05/11 12:07:19 by mrojouan         ###   ########.fr       */
>>>>>>> 95617388628850e32804878b73cb5e1b20d6b9ed
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*duplicate_wrd(char *str)
{
	char	*dup;
	int		len;

	len = word_len(str);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, str, len + 1);
	return (dup);
}

static void	skip_word(char *str, t_idx *idx)
{
	int	in_quotes;

	in_quotes = 0;
	while (str[idx->i])
	{
		if (str[idx->i] == '"' || str[idx->i] == '\'')
			in_quotes = !in_quotes;
		else if (!in_quotes && white_space(str[idx->i]))
			break ;
		idx->i++;
	}
}

static int	process_word(char *str, char **tab, t_idx *idx, t_shell *shell)
{
	tab[idx->j] = duplicate_wrd(str + idx->i);
	if (!tab[idx->j])
		return (0);
	tab[idx->j] = expand(tab[idx->j], shell);
	if (!tab[idx->j])
		return (0);
	skip_word(str, idx);
	return (1);
}

static int	fill_tab(char *str, char **tab, t_shell *shell)
{
	t_idx	idx;

	idx.i = 0;
	idx.j = 0;
	while (str[idx.i])
	{
		while (str[idx.i] && white_space(str[idx.i]))
			idx.i++;
		if (!str[idx.i])
			break ;
		if (!process_word(str, tab, &idx, shell))
		{
			ft_free_tab(tab);
			return (0);
		}
		idx.j++;
	}
	tab[idx.j] = 0;
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
