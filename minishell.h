/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:00:52 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/20 16:01:31 by mrojouan         ###   ########.fr       */
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

int	parsing(char *line, t_shell *shell);

#endif