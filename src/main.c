/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:09:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/03 11:55:13 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
			add_history(input);
		token = lexer(input);
		print_lexer(token);
		pipeline = parse(token);
		print_tree(pipeline);
		//print_tree_debug(pipeline);
		//is_syntax_error(pipeline);
		free_pipeline(&pipeline);
		input = readline(PROMPT);
	}
	return (0);
}
