/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:53:02 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/27 16:51:15 by malavaud         ###   ########.fr       */
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

int	is_word(const char *token)
{
	return (!is_operator(token));
}

static void	sort_line(char **split_line, t_shell *shell)
{
	int	i;
	int	j;
	int	k;
	int	arg_count;

	j = 0;
	i = 0;
	k = 0;
	arg_count = 0;
	shell->cmds[j] = malloc(sizeof(t_cmd));
	if (!shell->cmds[j])
		return ;
	while (split_line[i])
	{
		if (!ft_strcmp(split_line[i], "|"))
		{
			j++;
			shell->cmds[j] = malloc(sizeof(t_cmd));
			if (!shell->cmds[j])
				return ;
			k = 0;
		}
		else if (!ft_strcmp(split_line[i], "<<"))
			shell->cmds[j]->delimiter = split_line[++i];
		else if (!ft_strcmp(split_line[i], ">>"))
			shell->cmds[j]->insert = 1;
		else if (!ft_strcmp(split_line[i], "<"))
			shell->cmds[j]->infile = split_line[++i];
		else if (!ft_strcmp(split_line[i], ">"))
			shell->cmds[j]->outfile = split_line[++i];
		else
		{
			arg_count = 0;
			while (split_line[i + arg_count] && is_word(split_line[i + arg_count]))
				arg_count++;
			shell->cmds[j]->args = malloc(sizeof(char *) * (arg_count + 1));
			while (split_line[i] && is_word(split_line[i]))
			{
				shell->cmds[j]->args[k] = ft_strdup(split_line[i]);
				k++;
				i++;
			}
			shell->cmds[j]->args[k] = NULL;
			continue ;
		}
		i++;
	}
}

static int	count_cmds(char **split_line)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (split_line[i])
	{
		if (split_line[i][0] == '|')
			count++;
		i++;
	}
	return (count);
}

void    print_cmds(t_shell *shell, int cmd_count)
{
	int i;
	int k;

	i = 0;
	while (i < cmd_count)
	{
		printf("=== CMD %d ===\n", i);
		k = 0;
		if (shell->cmds[i]->args)
		{
			while (shell->cmds[i]->args[k])
			{
				printf("  args[%d] = %s\n", k, shell->cmds[i]->args[k]);
				k++;
			}
		}
		if (shell->cmds[i]->infile)
			printf("  infile    = %s\n", shell->cmds[i]->infile);
		if (shell->cmds[i]->outfile)
		   	printf("  outfile   = %s\n", shell->cmds[i]->outfile);
		if (shell->cmds[i]->delimiter)
			printf("  delimiter = %s\n", shell->cmds[i]->delimiter);
		if (shell->cmds[i]->insert)
			printf("  append    = yes\n");
		i++;
	}
}

int	parsing(char *line, t_shell *shell)
{
	char	**split_line;
	int		cmd_count;
	
	split_line = ft_split_space(line);
	if (!split_line)
		return (0);
	cmd_count = count_cmds(split_line);
	shell->cmds = malloc(sizeof(t_cmd) * (cmd_count + 1));
	if (!shell->cmds)
		return (0);
	sort_line(split_line, shell);
	print_cmds(shell, cmd_count);
	return (1);
}
