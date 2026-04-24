/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavaud <malavaud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 15:20:33 by mrojouan          #+#    #+#             */
/*   Updated: 2026/04/24 15:08:12 by malavaud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//static char	*prompt_making()
//{
//	char	*cwd;
//	char	*tmp;
//	char	*prompt;
	
//	cwd = getcwd(NULL, 0);
//	tmp = ft_strjoin(cwd, " >");
//	prompt = ft_strjoin(tmp, "$ ");
//	free(cwd);
//	free(tmp);
//	return (prompt);
//}

//static int	init_shell(t_shell *shell, char **envp)
//{
//	shell->cmds = NULL;
//	shell->env = envp;
//	shell->exit_status = 0;
//	return (0);
//}

//int	main(int ac, char **av, char **envp)
//{
//	char		*prompt;
//	char		*line;
//	t_shell		shell;

//	(void)ac;
//	(void)av;
//	init_shell(&shell, envp);
//	while (1)
//	{
//		prompt = prompt_making(); /* on cree notre ligne fixe "minishell >$"*/
//		line = readline(prompt); /* on affiche la ligne fixe et on attend une commande*/
//		free(prompt);
//		if (*line)
//			add_history(line); /* on ajoute la ligne a notre historique de ligne */
//		if (!parsing(line, &shell))
//			printf("problems");	
//	}
//}

//int main(int argc, char **argv, char **envp)
//{
//    t_shell shell;
//    char    *line;
//    char    *prompt;

//    (void)argc;
//    (void)argv;
//    init_shell(&shell, envp);
//    while (1)
//    {
//        prompt = prompt_making();
//        line = readline(prompt);
//        free(prompt);
//        if (!line)
//        {
//            printf("exit\n");
//            break;
//        }
//        if (*line)
//            add_history(line);
//        if (parsing(line, &shell) == 0)
//        {
//            free(line);
//            continue;
//        }
//        free(line);
//    }
//    return (shell.exit_status);
//}

int main(int argc, char **argv, char **envp)
{
	char *line;
	char *args[3];

	(void)argc;
	(void)argv;
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
			break;
		add_history(line);
		if (strncmp(line, "cd", 2) == 0)
		{
			args[0] = "cd";
			if (strlen(line) > 3)
				args[1] = line + 3;
			else
				args[1] = NULL;
			args[2] = NULL;
			ft_cd(args, envp);
		}
		else if (strcmp(line, "pwd") == 0)
		{
			char *cwd = getcwd(NULL, 0);
			printf("%s\n", cwd);
			free(cwd);
		}
		else
			printf("commande non gérée\n");
		free(line);
	}
	return (0);
}
