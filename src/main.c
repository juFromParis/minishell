/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:09:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/17 12:47:53 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

void	print_command(t_token *token)
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
	t_token	*command;
	char	*input;

	input = readline(PROMPT);
	while (input != NULL)
	{
		if (*input)
		{
			add_history(input);
		}
		command = lexer(input);
		free(input);
		print_command(command);
		free_command(&command);
		input = readline(PROMPT);
	}
	return (0);
}
