/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 09:34:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/03 20:09:18 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_node	*parse_or(t_token **cur)
{
	t_node	*left;
	t_node	*right;
	t_node	*node;

	left = parse_and(cur);
	if (!left)
		return (NULL);
	while (*cur && (*cur)->type == T_OR)
	{
		*cur = (*cur)->next;
		right = parse_and(cur);
		if (!right)
			return (free_ast(left), NULL);
		node = new_node(N_OR, left, right, NULL);
		if (!node)
			return (free_ast(left), free_ast(right), NULL);
		left = node;
	}
	return (left);
}

t_node	*parse_and(t_token **cur)
{
	t_node	*left;
	t_node	*right;
	t_node	*node;

	left = parse_pipe(cur);
	if (!left)
		return (NULL);
	while (*cur && (*cur)->type == T_AND)
	{
		*cur = (*cur)->next;
		right = parse_pipe(cur);
		if (!right)
			return (free_ast(left), NULL);
		node = new_node(N_AND, left, right, NULL);
		if (!node)
			return (free_ast(left), free_ast(right), NULL);
		left = node;
	}
	return (left);
}

t_node	*parse_pipe(t_token **cur)
{
	t_node	*left;
	t_node	*right;
	t_node	*node;

	left = parse_cmd(cur);
	if (!left)
		return (NULL);
	while (*cur && (*cur)->type == T_PIPE)
	{
		*cur = (*cur)->next;
		right = parse_cmd(cur);
		if (!right)
			return (free_ast(left), NULL);
		node = new_node(N_PIPE, left, right, NULL);
		if (!node)
			return (free_ast(left), free_ast(right), NULL);
		left = node;
	}
	return (left);
}

static int	is_cmd_token(t_token_type type)
{
	if (type == T_WORD)
		return (1);
	return (0);
}

t_node	*parse_cmd(t_token **cur)
{
	t_node	*node;
	t_node	*redir;

	if (!*cur)
		return (NULL);

	/* ------------------------- SUBSHELL ( ... ) ------------------------- */
	if ((*cur)->type == T_PARENT_OPEN)
	{
		*cur = (*cur)->next; // consume '('

		node = parse_or(cur); // parse inside parentheses
		if (!node)
			return (NULL);
		if (!*cur || (*cur)->type != T_PARENT_CLOSE)
		{
			free_ast(node);
			return (NULL);
		}
		*cur = (*cur)->next; // consume ')'

		return new_node(N_SUB, node, NULL, NULL);
	}

	/* ------------------------- SIMPLE COMMAND ------------------------- */
	if (is_cmd_token((*cur)->type))
	{
		node = new_node(N_CMD, NULL, NULL, (*cur)->value);
		if (!node)
			return (NULL);
		*cur = (*cur)->next;

		/* ---- parse arguments OR redirections ---- */
		while (*cur)
		{
			/* ------------------------- ARGUMENT ------------------------- */
			if ((*cur)->type == T_WORD)
			{
				// store last argument as node->cmd (upgrade later)
				free(node->cmd);
				node->cmd = NULL;
				*cur = (*cur)->next;
			}
			/* ------------------------- REDIRECTIONS --------------------- */
			else if ((*cur)->type == T_REDIR_IN || (*cur)->type == T_REDIR_OUT
				|| (*cur)->type == T_APPEND || (*cur)->type == T_HEREDOC)
			{
				*cur = (*cur)->next; // consume operator

				if (!*cur || (*cur)->type != T_WORD)
				{
					free_ast(node);
					return (NULL);
				}

				redir = new_node(N_REDIR_IN, NULL, NULL, NULL);
				if (!redir)
					return (free_ast(node), NULL);

				redir->file = ft_strdup((*cur)->value);
				redir->left = node;   // attach to command
				node = redir;         // new root of command subtree

				*cur = (*cur)->next;
			}

			else
				break;
		}
		return node;
	}
	return (NULL);
}


t_node	*parse(t_token *cur)
{
	t_node *ast;

	if (!cur)
		return NULL;

	ast = parse_or(&cur); 

	if (cur && cur->type != T_END)
	{
		fprintf(stderr, "minishell: syntax error near unexpected token `%s'\n",
				cur->value);
		free_ast(ast);
		return NULL;
	}

	return ast;
}
