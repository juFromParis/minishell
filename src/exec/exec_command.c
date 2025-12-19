/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/09 09:54:27 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/16 16:16:57 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins/builtins.h"
#include "../env/env.h"
#include "../utils/utils.h"
#include "exec.h"
#include "sys/wait.h"

static void	handle_exec_error(char *cmd)
{
	if (write(2, cmd, ft_strlen(cmd)) == -1)
		perror("write");
	if (write(2, ": command not found\n", 20) == -1)
		perror("write");
}

int	exec_command(char *pathname, char **args_null_terminated, t_env *env)
{
	pid_t	pid;
	int		status;

	if (!pathname || !args_null_terminated || !args_null_terminated[0] || !env)
		return (perror("exec_command: Invalid arguments\n"), -1);
	pid = fork();
	if (pid == -1)
		return (perror("fork"), -1);
	else if (pid == 0)
	{
		if (execve(pathname, args_null_terminated, to_envp(env)) == -1)
		{
			handle_exec_error(args_null_terminated[0]);
			exit(127);
		}
	}
	else
	{
		if (wait(&status) == -1)
			perror("wait");
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		return (-1);
	}
	return (0);
}

int	execute_command_node(t_node *node, t_env *env)
{
	int		exit_code;
	char	*path;

	path = NULL;
	if (!node || !env)
		return (perror("execute_command_node: Invalid arguments\n"), -1);
	printf("cmd1 = %s\n", node->cmd[0]);
	if ((node->cmd && is_builtin_command(node->cmd[0])) || (node->cmd2 && is_builtin_command(node->cmd2[0])))
	{
		return (execute_builtin_command(node, env));
	}
	path = resolve_path(node->cmd[0], env);
	if (!path)
	{
		handle_exec_error(node->cmd[0]);
		return (127);
	}
	exit_code = exec_command(path, node->cmd, env);
	free(path);
	return (exit_code);
}
