/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/27 14:25:25 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/27 14:26:40 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int is_operator(const char *token)
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

int is_word(const char *token)
{
    return (!is_operator(token));
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
