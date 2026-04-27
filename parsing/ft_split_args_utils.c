/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:48:46 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/27 15:49:46 by mrojouan         ###   ########.fr       */
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

int	word_len(char *str)
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