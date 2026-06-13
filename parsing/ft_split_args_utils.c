/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 15:48:46 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/13 21:05:17 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	white_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

//int	count_words(char *str)
//{
//	int	i;
//	int	count;
//	int	in_quotes;

//	i = 0;
//	count = 0;
//	in_quotes = 0;
//	if (!str || !str[0])
//		return (0);
//	while (str[i])
//	{
//		if (!white_space(str[i])
//			&& (i == 0 || (white_space(str[i - 1]) && !in_quotes)))
//			count++;
//		if (str[i] == '"' || str[i] == '\'')
//			in_quotes = !in_quotes;
//		i++;
//	}
//	return (count);
//}
int	count_words(char *str)
{
	int	i;
	int	count;
	int	in_single;
	int	in_double;

	i = 0;
	count = 0;
	in_single = 0;
	in_double = 0;
	if (!str || !str[0])
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (!white_space(str[i])
			&& (i == 0
			|| (white_space(str[i - 1])
			&& !in_single && !in_double)))
			count++;
		i++;
	}
	return (count);
}

char	*remove_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		in_single;
	int		in_double;

	res = malloc(ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

void	remove_cmd_quotes(t_shell *shell)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < shell->cmd_count)
	{
		j = 0;
		while (shell->cmds[i]->args && shell->cmds[i]->args[j])
		{
			tmp = remove_quotes(shell->cmds[i]->args[j]);
			free(shell->cmds[i]->args[j]);
			shell->cmds[i]->args[j] = tmp;
			j++;
		}
		i++;
	}
}

int	word_len(char *str)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		else if (white_space(str[i]) && !in_single && !in_double)
			break ;
		i++;
	}
	return (i);
}
