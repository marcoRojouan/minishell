/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:25:25 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/26 15:11:35 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	is_operator(const char *token)
{
	if (!token)
		return (0);
	if (!ft_strcmp(token, "|"))
		return (1);
	if (!ft_strcmp(token, ">"))
		return (1);
	if (!ft_strcmp(token, ">>"))
		return (1);
	if (!ft_strcmp(token, "<"))
		return (1);
	if (!ft_strcmp(token, "<<"))
		return (1);
	return (0);
}

static int	is_redir(const char *token)
{
	if (!token)
		return (0);
	if (!ft_strcmp(token, ">"))
		return (1);
	if (!ft_strcmp(token, ">>"))
		return (1);
	if (!ft_strcmp(token, "<"))
		return (1);
	if (!ft_strcmp(token, "<<"))
		return (1);
	return (0);
}

int	is_word(const char *token)
{
	return (!is_operator(token));
}

int	is_quote_closed(char *line)
{
	int	i;
	int	in_single;
	int	in_double;

	in_single = 0;
	in_double = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			in_single = !in_single;
		else if (line[i] == '"')
			in_double = !in_double;
		i++;
	}
	if (in_single || in_double)
		return (0);
	return (1);
}

int	is_in_order(char **split_line)
{
	int	i;

	i = 0;
	if (!ft_strcmp(split_line[i], "|"))
		return (0);
	while (split_line[i])
	{
		if (split_line[i][0] == '|' && split_line[i][1] != '\0')
			return (0);
		if (!ft_strcmp(split_line[i], "|"))
		{
			if (!split_line[i + 1] || !is_word(split_line[i + 1]))
				return (0);
		}
		if (is_redir(split_line[i]))
		{
			if (!split_line[i + 1] || !is_word(split_line[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}
