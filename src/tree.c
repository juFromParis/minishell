/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:55:02 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/18 20:21:12 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static const char *node_type_name(t_node_type type)
{
	if (type == N_START)        return "START";
    if (type == N_CMD)          return "CMD";
	if (type == N_WORD)         return "WORD";
	if (type == N_PIPE)         return "PIPE";
	if (type == N_REDIR_IN)     return "REDIR_IN";
	if (type == N_REDIR_OUT)    return "REDIR_OUT";
	if (type == N_HEREDOC)      return "HEREDOC";
	if (type == N_APPEND)       return "APPEND";
	if (type == N_END)          return "END";
	return "UNKNOWN";
}

static void	print_tree_rec(t_node *node, char *prefix, int last)
{
	// Print prefix
	printf("%s", prefix);

	// Print branch
	if (last)
		printf(" -> ");
	else
		printf(" -> ");

	// Print node itself
	printf("[%s]", node_type_name(node->type));
	if (node->value)
		printf(" %s", node->value);
	printf("\n");

	// Prepare new prefix
	char new_prefix[256];
	snprintf(new_prefix, sizeof(new_prefix), "%s%s",
		prefix, last ? "    " : "    ");

	// Count siblings to know which one is last
	t_node *child = node->child;
	while (child)
	{
		int is_last = (child->sibling == NULL);
		print_tree_rec(child, new_prefix, is_last);
		child = child->sibling;
	}
}

void	print_tree(t_node *root)
{
	if (!root)
		return;

	// Print root without prefix
	printf("%s\n", node_type_name(root->type));

	t_node *child = root->child;
	while (child)
	{
		int last = (child->sibling == NULL);
		print_tree_rec(child, "", last);
		child = child->sibling;
	}
}
