/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:28:36 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/16 14:21:15 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void 	sig_init(void)
{
	sig_start(SIGINT, sigint_listener);
	sig_start(SIGTERM, sigterm_listener);
	sig_start(SIGQUIT, SIG_IGN);
}

void sig_start(int signum, void (*handler)(int))
{
    struct sigaction sig;

    sig.sa_handler = handler;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = SA_RESTART;
    sigaction(signum, &sig, NULL);
}

void	sigint_listener(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigterm_listener(int sig)
{
	(void)sig;
	write(1, "exit\n", 5);
	rl_clear_history();
	exit(128 + SIGTERM);
}
