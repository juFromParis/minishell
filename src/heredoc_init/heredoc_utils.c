/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 10:52:01 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/04 11:15:03 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	hd_interrupted(int status)
{
	if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		return (1);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		return (1);
	return (0);
}

void	hd_parent_signals(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	hd_restore_signals(void)
{
	sig_start(SIGINT, sigint_prompt);
	sig_start(SIGQUIT, sigquit_ignore);
}

int	hd_fork_and_wait(t_heredoc *h, int fd_read, int fd_write)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close(fd_read);
		heredoc_child(h, fd_write);
		exit(0);
	}
	close(fd_write);
	waitpid(pid, &status, 0);
	return (status);
}
