/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:00:52 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/27 14:27:44 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <libft.h>

typedef struct s_cmd
{
	char			**args;
	char			*infile;
	char			*outfile;
	char			*delimiter;

	int				insert;
	
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_cmd			**cmds;
	
	char			**env;
	int				exit_status;
}	t_shell;

int		parsing(char *line, t_shell *shell);
int		is_operator(const char *token);
int		is_word(const char *token);

char	*expand(char *elem, t_shell *shell);
char	**ft_split_args(char *str, t_shell *shell);

void	expand_var(char *elem, char *res, int *i, int *j, t_shell *shell);
void	expand_status(char *res, int *i, int *j, t_shell *shell);
void	handle_quotes(char *elem, int *i, int *in_single, int *in_double);

// A ENLEVER A LA FIN
void    print_cmds(t_shell *shell, int cmd_count);

#endif