/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:09:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/18 19:56:57 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static const char *node_type_name(t_node_type type)
{
	if (type == N_START)        return "START";
	if (type == N_WORD)         return "WORD";
	if (type == N_PIPE)         return "PIPE";
	if (type == N_REDIR_IN)     return "REDIR_IN";
	if (type == N_REDIR_OUT)    return "REDIR_OUT";
	if (type == N_HEREDOC)      return "HEREDOC";
	if (type == N_APPEND)       return "APPEND";
	if (type == N_END)          return "END";
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
        case T_WORD: return "T_WORD";
        case T_PIPE: return "T_PIPE";
        case T_REDIR_IN: return "T_REDIR_IN";
        case T_REDIR_OUT: return "T_REDIR_OUT";
        case T_HEREDOC: return "T_HEREDOC";
        case T_APPEND: return "T_APPEND";
        case T_SQUOTE: return "T_SQUOTE";
        case T_DQUOTE: return "T_DQUOTE";
		case T_PARENT_OPEN: return "T_PARENT_OPEN";
		case T_PARENT_CLOSE: return "T_PARENT_CLOSE";
		case T_END: return "T_END";
		case T_AND: return "T_AND";
        case T_OR: return "T_OR";
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

int	main(void)
{
	t_token	*token;
	t_node	*pipeline;
	char	*input;

	token = NULL;
	pipeline = NULL;
	input = readline(PROMPT);
	while (input != NULL)
	{
		if (*input)
		{
			add_history(input);
		}
		token = lexer(input);
		free(input);
		//print_lexer(token);
		pipeline = parse(token);
		print_tree(pipeline);
		free_lexer(&token);
		free(pipeline);
		input = readline(PROMPT);
	}
	return (0);

}
