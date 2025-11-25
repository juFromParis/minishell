/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:52:57 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/25 11:54:53 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

static const char *node_type_name(t_token_type type)
{
	if (type == START)        return "START";
	if (type == SUB)          return "SUB";
    if (type == CMD)          return "CMD";
	if (type == WORD)         return "WORD";
	if (type == PIPE)         return "PIPE";
	if (type == REDIR_IN)     return "REDIR_IN";
	if (type == REDIR_OUT)    return "REDIR_OUT";
	if (type == HEREDOC)      return "HEREDOC";
	if (type == APPEND)       return "APPEND";
	if (type == END)          return "END";
	return "UNKNOWN";
}
void	print_parse(t_node *node)
{
	if (!node)
		return ;

	printf("Node type: %s", node_type_name(node->type));
    if (node->value)
        printf(" | value: \"%s\"", node->value);
    printf("\n");

    // afficher les enfants
    if (node->child)
        print_parse(node->child);

    // afficher les siblings
    if (node->sibling)
        print_parse(node->sibling);
}

const	char	*token_type_to_str(t_token_type type)
{
	switch (type)
    {
        case WORD: return "T_WORD";
        case PIPE: return "T_PIPE";
        case REDIR_IN: return "T_REDIR_IN";
        case REDIR_OUT: return "T_REDIR_OUT";
        case HEREDOC: return "T_HEREDOC";
        case APPEND: return "T_APPEND";
        case SQUOTE: return "T_SQUOTE";
        case DQUOTE: return "T_DQUOTE";
		case PARENT_OPEN: return "T_PARENT_OPEN";
		case PARENT_CLOSE: return "T_PARENT_CLOSE";
		case END: return "T_END";
		case AND: return "T_AND";
        case OR: return "T_OR";
        default: return "UNKNOWN";
	}
}

void	print_lexer(t_token *token)
{
	t_token	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("[%s] [%s]\n", token_type_to_str(tmp->type), tmp->value);
		tmp = tmp->next;
	}
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
