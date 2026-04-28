/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:00:52 by mrojouan          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2026/04/27 16:50:20 by malavaud         ###   ########.fr       */
=======
/*   Updated: 2026/04/22 14:46:35 by malavaud         ###   ########.fr       */
>>>>>>> 8ae562372bc1c22abdf325f0ad784c64d87994b0
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
char	**copy_env(char **envp);

int	ft_echo(char **args);

#endif