/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrojouan <mrojouan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 16:14:49 by mrojouan          #+#    #+#             */
/*   Updated: 2026/06/10 10:08:56 by mrojouan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

volatile sig_atomic_t signal_g = 0;

void heredoc_sigint(int sig)
{
    (void)sig;
    write(1, "\n", 1);
    close(STDIN_FILENO);
    signal_g = SIGINT;
}

void	sigint_handler(int sig)
{
	(void)sig;
	signal_g = SIGINT;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
    signal(SIGQUIT, SIG_IGN);
}
