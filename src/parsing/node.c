/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:47:28 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/03 19:07:40 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*new_node(t_node_type type, t_node *left, t_node *right, char *cmd)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->parent = NULL;
	node->left = left;
	node->right = right;
	node->file = NULL;
	if (cmd)
		node->cmd = NULL;
	else
		node->cmd = NULL;
	return (node);
}

