/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:09:21 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/17 16:04:24 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "./env/env.h"
#include "./exec/exec.h"

volatile sig_atomic_t	g_heredoc_interrupted = 0;
volatile int			g_exit_status = 0;

static char	*start_shell(char *input, t_env *envp)
{
	t_token	*token;
	t_node	*ast;

	if (*input)
		add_history(input);
	token = lexer(input);
	is_syntax_error(token);
	//print_lexer(token);
	ast = parse(token);
	free_lexer(&token);
	if (!heredoc_init(ast))
	{
		sig_start(SIGINT, sigint_exec);
		execute_ast(ast, envp);
	}
	//print_tree(ast);
	free_ast(ast);
	sig_start(SIGINT, sigint_prompt);
	free(input);
	return (readline(get_env_value(envp, "PROMPT")));
}

int	main(int argc, char **argv, char **envp_raw)
{
	t_env	*envp;
	char	*input;

	(void)argc;
	(void)argv;
	envp = parse_env(envp_raw);
	if (!envp)
		return (1);
	sig_start(SIGINT, sigint_prompt);
	sig_start(SIGQUIT, sigquit_ignore);
	input = readline(get_env_value(envp, "PROMPT"));
	while (input)
		input = start_shell(input, envp);
	write(1, "exit\n", 5);
	free_env(envp);
	return (g_exit_status);
}
