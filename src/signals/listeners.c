/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   listeners.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 21:28:36 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/04 10:35:07 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../env/env.h"

void	sig_start(int signum, void (*handler)(int))
{
	struct sigaction	sig;

	sig.sa_handler = handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	sigaction(signum, &sig, NULL);
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	g_exit_status = 130;
	g_heredoc_interrupted = 1;
	write(1, "\n", 1);
	rl_done = 1;
}


void	sigint_prompt(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigint_exec(int sig)
{
	(void)sig;
	g_exit_status = 130;
	write(1, "\n", 1);
}

void	sigquit_ignore(int sig)
{
	(void)sig;
}
