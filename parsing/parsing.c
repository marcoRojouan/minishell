/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:53:02 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/20 16:40:46 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
if (1er element du split == <)
	le +1 = infile
// if (1er element du split == <<)
// 	heredoc = 1;
shell->cmds[i]->args = {cat, -e}
if (split[i] == '|')
	on peut continuer et passer a la commande suivante
shell->cmds[i]->args = {grep, v}
if (split [i] == > ou >>)
	if (>>)
		insert = 1 
	le +1 = outfile
sinon c bon finito pipeau
*/


static void sort_line(char **split_line, t_shell *shell)
{
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	shell->cmds[j] = malloc(sizeof(t_cmd));
	if (!shell->cmds[j])
		return ;
	while (split_line[i])
	{
		if (!ft_strncmp(split_line[i], "|", 1))
		{
			j++;
			shell->cmds[j] = malloc(sizeof(t_cmd));
			if (!shell->cmds[j])
				return ;
			k = 0;
		}
		else if (!ft_strncmp(split_line[i], "<<", 2))
			shell->cmds[j]->delimiter = split_line[++i];
		else if (!ft_strncmp(split_line[i], ">>", 2))
			shell->cmds[j]->insert = 1;
		else if (!ft_strncmp(split_line[i], "<", 1))
			shell->cmds[j]->infile = split_line[++i];
		else if (!ft_strncmp(split_line[i], ">", 1))
			shell->cmds[j]->outfile = split_line[++i];
		else
		{
			/* changer cette partie ca ne s'arrete pas si la commande est finie*/
			shell->cmds[j]->args = malloc(sizeof(char *) * 3);
			shell->cmds[j]->args[k] = split_line[i++];
			k++;
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
