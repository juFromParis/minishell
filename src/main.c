/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 10:09:21 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/04 13:42:27 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "./env/env.h"
#include "./exec/exec.h"
#include <unistd.h>

volatile sig_atomic_t	g_heredoc_interrupted = 0;
volatile int			g_exit_status = 0;

static char	*ms_readline(t_env *envp)
{
	if (isatty(STDIN_FILENO))
		return (readline(get_env_value(envp, "PROMPT")));
	return (readline("")); /* pas de prompt en non-interactif */
}

static char	*start_shell(char *input, t_env *envp)
{
	t_token	*token;
	t_node	*ast;

	if (!input)
		return (NULL);
	if (*input && isatty(STDIN_FILENO))
		add_history(input);
	token = lexer(input);
	is_syntax_error(token);
	ast = parse(token);
	free_lexer(&token);
	if (!ast)
	{
		sig_start(SIGINT, sigint_prompt);
		free(input);
		return (readline(get_env_value(envp, "PROMPT")));
	}
	if (!heredoc_init(ast))
	{
		sig_start(SIGINT, sigint_exec);
		execute_ast(ast, envp);
	}
	free_ast(ast);
	sig_start(SIGINT, sigint_prompt);
	free(input);
	return (ms_readline(envp));
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
	input = ms_readline(envp);
	while (input)
		input = start_shell(input, envp);
	if (isatty(STDIN_FILENO))
		write(1, "exit\n", 5);
	free_env(envp);
	return (g_exit_status);
}
