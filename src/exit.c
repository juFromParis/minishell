/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:18:01 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/25 14:03:47 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_lexer(t_token **list)
{
	t_token	*tmp;
	t_token	*current;

	current = *list;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
	*list = NULL;
}

void	free_pipeline(t_node **list)
{
	t_node	*node;
	t_node	*child;
	t_node	*sibling;

	if (!list || !*list)
		return ;
	node = *list;
	child = node->child;
	while (child)
	{
		sibling = child->sibling;
		free_pipeline(&child);
		child = sibling;
	}
	if (node->value)
		free(node->value);
	if (node->sibling)
		free_pipeline(&node->sibling);
	free(node);
	*list = NULL;
}
