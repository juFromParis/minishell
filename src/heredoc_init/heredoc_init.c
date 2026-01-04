/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:18:42 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/04 11:22:26 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

static char	*read_all_fd(int fd)
{
	char	buf[1024];
	char	*res;
	char	*tmp;
	ssize_t	n;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	n = read(fd, buf, sizeof(buf));
	while (n > 0)
	{
		buf[n] = '\0';
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
		n = read(fd, buf, sizeof(buf));
	}
	return (res);
}

void	heredoc_child(t_heredoc *h, int fd)
{
	char	*line;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("> ");
		if (!line)
			exit(0);
		if (!ft_strcmp(line, h->delimiter))
		{
			free(line);
			exit(0);
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
}

static int	handle_heredoc_node(t_node *node)
{
	int	fd[2];
	int	status;

	if (!node->heredocs)
		return (0);
	if (pipe(fd) == -1)
		return (1);
	hd_parent_signals();
	status = hd_fork_and_wait(node->heredocs, fd[0], fd[1]);
	hd_restore_signals();
	if (hd_interrupted(status))
		return (close(fd[0]), g_exit_status = 130, 1);
	free(node->heredoc);
	node->heredoc = read_all_fd(fd[0]);
	close(fd[0]);
	return (0);
}

int	heredoc_init(t_node *node)
{
	if (!node)
		return (0);
	if (handle_heredoc_node(node))
		return (1);
	if (heredoc_init(node->left))
		return (1);
	if (heredoc_init(node->right))
		return (1);
	return (0);
}
