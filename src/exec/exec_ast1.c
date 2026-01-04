/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_ast1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 18:41:27 by vtaniga           #+#    #+#             */
/*   Updated: 2026/01/04 13:43:38 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../env/env.h"
#include "../utils/utils.h"
#include "exec.h"
#include <fcntl.h>

static char	*build_candidate(char *dir, char *cmd)
{
	char	*tmp;
	char	*candidate;

	if (!dir || !cmd)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	candidate = ft_strjoin(tmp, cmd);
	free(tmp);
	return (candidate);
}

static char	*find_executable_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*candidate;

	if (!paths || !cmd)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		candidate = build_candidate(paths[i], cmd);
		if (!candidate)
		{
			free_splitted(paths);
			return (NULL);
		}
		if (path_check(candidate) == 1)
		{
			free_splitted(paths);
			return (candidate);
		}
		free(candidate);
		i++;
	}
	free_splitted(paths);
	return (NULL);
}

char	*resolve_path(char *cmd, t_env *env)
{
	char	*path;
	char	**paths;

	if (!cmd || !env)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = get_env_value(env, "PATH");
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	if (!paths)
		return (NULL);
	return (find_executable_in_paths(paths, cmd));
}

// char	**build_args_array(t_node *node)
// {
// 	return (node->arg);
// }

int	execute_ast(t_node *node, t_env *env)
{
	char	*content;

	content = NULL;
	(void)content;
	if (!node || !env)
		return (0);
	if (node->redir && ft_strncmp(node->redir, ">", 2) == 0)
		return (execute_redir_out_node(node, env));
	if (node->redir && ft_strncmp(node->redir, "<", 2) == 0)
		return (execute_redir_in_node(node, env));
	if (node->redir && ft_strncmp(node->redir, ">>", 3) == 0)
		return (execute_append_node(node, env));
	if (node->redir && ft_strncmp(node->redir, "<<", 3) == 0)
		return (execute_heredoc_node(node, env));
	if (node->type == N_CMD)
		return (execute_command_node(node, env));
	if (node->type == N_PIPE)
		return (execute_pipe_node(node, env));
	if (node->type == N_AND)
		return (execute_and_node(node, env));
	if (node->type == N_OR)
		return (execute_or_node(node, env));
	return (0);
}
