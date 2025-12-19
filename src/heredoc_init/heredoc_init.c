/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 10:18:42 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/17 12:55:49 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../inc/minishell.h"
#include "../utils/utils.h"

char	*read_all_fd(int fd)
{
	char	buf[1024];
	char	*res;
	char	*tmp;
	ssize_t	n;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	while ((n = read(fd, buf, sizeof(buf))) > 0)
	{
		buf[n] = '\0';
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
	}
	return (res);
}

void	read_one_heredoc(t_heredoc *h_node)
{
	char	*input;

	while (!g_heredoc_interrupted)
	{
		input = readline("> ");
		if (!input || g_heredoc_interrupted)
		{
			free(input);
			return ;
		}
		if (!ft_strcmp(input, h_node->delimiter))
		{
			free(input);
			return ;
		}
		ft_append(&h_node->content, input);
		free(input);
	}
}

static void	heredoc_child(t_heredoc *h, int fd)
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
	int		fd[2];
	pid_t	pid;
	int		status;

	if (!node->heredocs)
		return (0);
	if (pipe(fd) == -1)
		return (1);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		heredoc_child(node->heredocs, fd[1]);
		exit(0);
	}
	close(fd[1]);
	waitpid(pid, &status, 0);
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
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
