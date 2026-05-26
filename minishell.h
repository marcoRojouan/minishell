/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:00:52 by mrojouan          #+#    #+#             */
/*   Updated: 2026/05/26 15:11:24 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
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

	int				cmd_count;
	int				exit_status;
}	t_shell;

typedef struct s_context
{
    int     i;
    int     j;
    int     k;
}   t_context;

typedef struct s_idx
{
    int     i;
    int     j;
}   t_idx;


int		parsing(char *line, t_shell *shell);
int		is_operator(const char *token);
int		is_word(const char *token);
int		is_quote_closed(char *line);
int		is_in_order(char **split_line);

int		exec_pipeline(t_shell *shell);
void	fd_gestion(t_shell *shell, int **pipes, int i);
int 	exec_caller(t_shell *shell);

int		white_space(char c);
int		count_words(char *str);
int		word_len(char *str);

int		ft_cd(char **args, char **env);
int		ft_echo(char **args);
int		ft_pwd(void);
char	**ft_export(char **args, char **env);
void	ft_env(char **env);
char	**set_env(char **env, char *key, char *value);
char	*get_env(char **env, char *key);
int		valid_key(char *key);
int		ft_unset(char **args, char **env);

char	*expand(char *elem, t_shell *shell);
char	**ft_split_args(char *str, t_shell *shell);
char	**copy_env(char **envp);

void	expand_var(char *elem, char *res, t_idx *ctx, t_shell *shell);
void	expand_status(char *res, t_idx *ctx, t_shell *shell);
void	handle_quotes(char *elem, t_idx *ctx, int *in_single, int *in_double);
void	sort_line(char **split_line, t_shell *shell);

#endif