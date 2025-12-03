/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 10:52:57 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/03 12:13:15 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

# define LEXER_COLOR     "\033[35m"
# define AST_COLOR   "\033[36m"
# define RESPONSE_COLOR   "\033[33m"
# define RESET   "\033[0m"

static const char *node_type_name(t_token_type type)
{
	if (type == START)        return "START";
	if (type == SUB)          return "SUB";
    if (type == PARENT_OPEN)          return "PARENT_OPEN";
    if (type == PARENT_CLOSE)          return "PARENT_CLOSE";
	if (type == OPE)          return "OPE";
	if (type == PIPE)         return "PIPE";
	if (type == AND)          return "AND";
	if (type == OR)           return "OR";
    if (type == CMD)          return "CMD";
	if (type == WORD)         return "WORD";
	if (type == PIPE)         return "PIPE";
    if (type == RDR)          return "RDR";
	if (type == REDIR_IN)     return "REDIR_IN";
	if (type == REDIR_OUT)    return "REDIR_OUT";
    if (type == APPEND)      return "APPEND";
	if (type == HEREDOC)      return "HEREDOC";
	if (type == BUILTIN)       return "BUILTIN";
    if (type == FCT)       return "FCT";
    if (type == ECHO)       return "ECHO";
    if (type == CD)       return "CD";
    if (type == PWD)       return "PWD";
    if (type == EXPORT)       return "EXPORT";
    if (type == UNSET)       return "UNSET";
    if (type == ENV)       return "ENV";
    if (type == EXIT)       return "EXIT";
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
        case WORD: return "WORD";
        case OPE: return "OPE";
        case PIPE: return "PIPE";
        case RDR: return "RDR";
        case REDIR_IN: return "REDIR_IN";
        case REDIR_OUT: return "REDIR_OUT";
        case HEREDOC: return "HEREDOC";
        case APPEND: return "APPEND";
        case SQUOTE: return "SQUOTE";
        case DQUOTE: return "DQUOTE";
		case PARENT_OPEN: return "PARENT_OPEN";
		case PARENT_CLOSE: return "PARENT_CLOSE";
		case END: return "END";
		case AND: return "AND";
        case OR: return "OR";
        case BUILTIN: return "BUILTIN";
        case FCT: return "FCT";
        case ECHO: return "ECHO";
        case CD: return "CD";
        case PWD: return "PWD";
        case EXPORT: return "EXPORT";
        case UNSET: return "UNSET";
        case ENV: return "ENV";
        case EXIT: return "EXIT";
        default: return "UNKNOWN";
	}
}

void	print_lexer(t_token *token)
{
	t_token	*tmp;

	tmp = token;
    printf(LEXER_COLOR "\n/--LEXER------------------------------------------------------------------------------------------/\n\n" RESET);
	while (tmp)
	{
		printf(LEXER_COLOR "[ %s : %s ]" RESET, token_type_to_str(tmp->type), tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

static void print_tree_rec(t_node *node, char *prefix, int last)
{
    if (!node)
        return;

    // Affiche le préfixe
    printf(AST_COLOR "%s" RESET, prefix);

    // Affiche la branche
    printf(AST_COLOR " -> " RESET);

    // Affiche le noeud lui-même
    printf(AST_COLOR "[%s]" RESET, node_type_name(node->type));
    if (node->value)  // Si le nœud a une valeur (ce sera le cas pour les opérateurs)
        printf(AST_COLOR "     %s" RESET, node->value);

    // Affiche previous pour tous les noeuds
    printf(AST_COLOR " // node=%p // prev=%p // parent=%p" RESET, node, node->previous, node->parent);

    printf("\n");

    // Prépare le nouveau préfixe pour les enfants
    char new_prefix[256];
    snprintf(new_prefix, sizeof(new_prefix), "%s%s",
             prefix, last ? "    " : "│   ");

    // Parcourt tous les enfants
    t_node *child = node->child;
    while (child)
    {
        int is_last = (child->sibling == NULL);
        print_tree_rec(child, new_prefix, is_last);  // Appel récursif pour afficher l'enfant
        child = child->sibling;
    }
}

void print_tree(t_node *root)
{
    if (!root)
        return;

    printf(AST_COLOR "\n/--AST--------------------------------------------------------------------------------------------/\n\n" RESET);

    // Affiche la racine sans préfixe
    printf(AST_COLOR "[%s]" RESET, node_type_name(root->type));

    printf(AST_COLOR "%s\n" RESET, root->value);

    t_node *child = root->child;
    while (child)
    {
        int last = (child->sibling == NULL);
        print_tree_rec(child, "", last);  // Affiche récursivement les enfants
        child = child->sibling;
    }

    printf(RESPONSE_COLOR "\n/--REPONSE----------------------------------------------------------------------------------------/\n\n" RESET);
}

void print_node_debug(t_node *node, int depth)
{
    if (!node)
        return;

    // indentation
    for (int i = 0; i < depth; i++)
        printf("    ");

    // Node info
    printf("[%s", node_type_name(node->type));
    if (node->value)
        printf(" \"%s\"", node->value);
    printf("]\n");

    // Relations
    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("    ├── parent  → %p\n", node->parent);

    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("    ├── previous→ %p\n", node->previous);

    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("    ├── child   → %p", node->child);
    if (node->child)
    {
        printf("  (%s", node_type_name(node->child->type));
        if (node->child->value)
            printf(" \"%s\"", node->child->value);
        printf(")");
    }
    printf("\n");

    for (int i = 0; i < depth; i++)
        printf("    ");
    printf("    └── sibling → %p", node->sibling);
    if (node->sibling)
    {
        printf("  (%s", node_type_name(node->sibling->type));
        if (node->sibling->value)
            printf(" \"%s\"", node->sibling->value);
        printf(")");
    }
    printf("\n\n");

    // Recursion
    print_node_debug(node->child, depth + 1);
    print_node_debug(node->sibling, depth);
}

void print_tree_debug(t_node *root)
{
    printf("\n====== DEBUG AST (child/sibling view) ======\n\n");
    print_node_debug(root, 0);
    printf("===========================================\n");
}
