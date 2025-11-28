/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:24:05 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/28 10:18:06 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node *parse_sub(t_token **cur)
{
	t_node	*sub;
	t_node	*node;

	if (!cur || !*cur || (*cur)->type != PARENT_OPEN)
		return (NULL);
	*cur = (*cur)->next;
	sub = new_node(SUB, NULL);
	if (!sub)
		return (NULL);
	while (*cur && (*cur)->type != PARENT_CLOSE)
	{
		if ((*cur)->type == PARENT_OPEN)
		{
			node = parse_sub(cur);
			lst_add_child(sub, node);
			continue ;
		}
		else if ((*cur)->type == WORD || ft_isredir((*cur)->value))
		{
			node = new_node((*cur)->type, (*cur)->value);
			lst_add_child(sub, node);
		}
		else if (ft_isbuiltin((*cur)->type))
		{
			node = new_node(FCT, (*cur)->value);
			lst_add_child(sub, node);
		}
		else if ((*cur)->type == OPE)
		{
			node = new_node(OPE, (*cur)->value);
			lst_add_child(sub, node);
		}
		*cur = (*cur)->next;
	}
	if (*cur && (*cur)->type == PARENT_CLOSE)
		*cur = (*cur)->next;
	return (sub);
}



t_node	*parse_left(t_token **cur)
{
	t_node	*node;

	if (!cur || !*cur)
		return (NULL);
	if (ft_isoperator((*cur)->type))
		return (NULL);
	node = new_node(CMD, NULL);
	if (!node)
		return (NULL);
	parse_cmd(node, cur);
	return (node);
}

void	parse_cmd(t_node *cmd, t_token **cur)
{
	t_node	*node;
	t_node	*sub;

	while (*cur && !ft_isoperator((*cur)->type) && (*cur)->type != PARENT_CLOSE)
	{
		if ((*cur)->type == PARENT_OPEN)
		{
			sub = parse_sub(cur);
			lst_add_child(cmd, sub);
			continue ;
		}
		else if (ft_isredir((*cur)->value))
		{
			node = new_node(RDR, (*cur)->value);
			lst_add_child(cmd, node);
		}
		else if ((*cur)->type == WORD)
		{
			node = new_node(WORD, (*cur)->value);
			lst_add_child(cmd, node);
		}
		else if (ft_isbuiltin((*cur)->type))
		{
			node = new_node(FCT, (*cur)->value);
			lst_add_child(cmd, node);
		}
		*cur = (*cur)->next;
	}
}

t_node	*parse(t_token *cur)
{
	t_node	*pipeline;
	t_node	*cmd;
	t_node	*operator;
	t_token	*tmp;

	if (!cur)
		return (NULL);
	tmp = cur;
	pipeline = new_node(START, NULL);
	if (!pipeline)
		return (NULL);
	while (cur && cur->type != END)
	{
		cmd = parse_left(&cur);
		if (!cmd && !ft_isoperator(cur->type))
			break ;
		if (cmd)
			lst_add_child(pipeline, cmd);
		if (cur && ft_isoperator(cur->type))
		{
			operator = new_node(OPE, cur->value);
			lst_add_child(pipeline, operator);
			cur = cur->next;
		}
	}
	free_lexer(&tmp);
	return (pipeline);
}
