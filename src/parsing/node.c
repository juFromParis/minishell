/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:47:28 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/18 18:52:44 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*new_node(t_node_type type, char *value)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->value = value;
	node->child = (NULL);
	node->sibling = (NULL);
	return (node);
}

void	lst_add_child(t_node *node, t_node *new)
{
	t_node	*last;

	if (!node || !new)
		return ;

	if (node->child == NULL)
	{
		node->child = new;
		return ;
	}
	last = node->child;
	while (last->sibling)
		last = last->sibling;
	last->sibling = new;
}

void	lst_add_sibling(t_node *node, t_node *new)
{
	t_node	*last;

	if (!node || !new)
		return ;

	last = node;
	while (last->sibling)
		last = last->sibling;
	last->sibling = new;
}
