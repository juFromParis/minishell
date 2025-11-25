/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:24:05 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/25 12:40:21 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redir(t_token_type type)
{
	if (type == REDIR_IN
		|| type == REDIR_OUT
		|| type == HEREDOC
		|| type == APPEND)
		return (1);
	return (0);
}

t_node	*parse_sub(t_token **cur)
{
	t_node	*sub;
	t_node	*cmd;

	if (!cur || !*cur || (*cur)->type != PARENT_OPEN)
		return (NULL);
	*cur = (*cur)->next;

	sub = new_node(SUB, NULL);
	if (!sub)
		return (NULL);
	while (*cur && (*cur)->type != PARENT_CLOSE)
	{
		cmd = parse_left(cur);
		if (!cmd)
			break ;
		lst_add_child(sub, cmd);
		if (*cur && (*cur)->type == PIPE)
			*cur = (*cur)->next;
	}
	if (*cur && (*cur)->type == PARENT_CLOSE)
		*cur = (*cur)->next;
	return (sub);
}

t_node	*parse_left(t_token **cur)
{
	t_node	*cmd;

	if (!cur || !*cur)
		return (NULL);
	//if (*cur && (*cur)->type == PARENT_OPEN)
	//	return (parse_sub(cur));
	cmd = new_node(CMD, NULL);
	if (!cmd)
		return (NULL);
	parse_cmd(cmd, cur);
	return (cmd);
}


void	parse_cmd(t_node *cmd, t_token **cur)
{
	t_node	*node;
	t_node	*sub;

	while (*cur && (*cur)->type != PIPE && (*cur)->type != PARENT_CLOSE)
	{
		if ((*cur)->type == PARENT_OPEN)
		{
			sub = parse_sub(cur);
			if (sub)
				lst_add_child(cmd, sub);
			continue ;
		}
		if (is_redir((*cur)->type))
			redir_node(cmd, *cur);
		else if ((*cur)->type == WORD)
		{
			node = new_node((*cur)->type, (*cur)->value);
			lst_add_child(cmd, node);
		}
		*cur = (*cur)->next;
	}
}

t_node	*parse(t_token *cur)
{
	t_node	*pipeline;
	t_node	*cmd;

	if (!cur)
		return (NULL);
	pipeline = new_node(START, NULL);
	if (!pipeline)
		return (NULL);
	while (cur)
	{
		cmd = parse_left(&cur);
		if (!cmd)
			break ;
		lst_add_child(pipeline, cmd);
		if (cur && cur->type == PIPE)
			cur = cur->next;
	}
	return (pipeline);
}
