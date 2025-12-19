/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir_in.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 12:11:20 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 17:29:32 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"
#include "exec.h"
#include <sys/wait.h>

static int	prepare_input_fd(const t_node *node)
{
	int	fd;

	if (node->file == NULL)
		return (perror("no file for redirection"), -1);
	fd = open(node->file, O_RDONLY);
	if (fd == -1)
		return (perror("open"), -1);
	return (fd);
}

static int	run_child_with_stdin(int fd, char **cmd, t_env *env)
{
	char	*path;
	int		exit_code;

	if (dup2(fd, STDIN_FILENO) == -1)
		return (perror("dup2"), -1);
	if (close(fd) == -1)
		return (perror("close"), -1);
	path = resolve_path(cmd[0], env);
	if (!path)
		return (perror("resolve_path"), -1);
	exit_code = exec_command(path, cmd, env);
	free(path);
	exit(exit_code);
}

static int	wait_child_status(pid_t pid)
{
	int	status;

	if (waitpid(pid, &status, 0) == -1)
		return (perror("waitpid"), -1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (-1);
}

int	execute_redir_in_node(t_node *node, t_env *env)
{
	int		fd;
	pid_t	pid;
	char	**cmd;

	if (!node || !env)
		return (perror("Invalid arguments to execute_redir_in_node"), -1);
	fd = prepare_input_fd(node);
	if (fd < 0)
		return (-1);
	if (node->cmd2)
		cmd = node->cmd2;
	else
		cmd = node->cmd;
	if (!cmd || !cmd[0])
		return (close(fd), perror("invalid command"), -1);
	pid = fork();
	if (pid < 0)
		return (close(fd), perror("fork"), -1);
	if (pid == 0)
		run_child_with_stdin(fd, cmd, env);
	if (close(fd) == -1)
		return (perror("close"), -1);
	return (wait_child_status(pid));
}
