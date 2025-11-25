/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:06:35 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/25 13:29:28 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\001\033[1;33m\002-minishell> \001\033[0m\002"

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_type
{
	START,
	SUB,
	CMD,
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	SQUOTE,
	DQUOTE,
	PARENT_OPEN,
	PARENT_CLOSE,
	AND,
	OR,
	END
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct		s_token	*next;
}	t_token;

typedef struct  s_node
{
	t_token_type		type;
	char				*value;
	struct		s_node	*child;
	struct		s_node	*sibling;
}	t_node;

// UTILS
int	ft_isoperator(char c);
int	ft_isspace(char c);
char	*ft_strdup(char *src);
char	*ft_strndup(const char *s, size_t n);

// LEXER & PARSING
t_token	*lexer(char *str);
t_token *new_token(t_token_type type, char *value);
t_token *check_operator(char *str, int *i);
t_token	*check_word(char *str, int *i);
void	token_add_back(t_token **list, t_token *new);
void	token_push(t_token **list, t_token *token, int *i);
void	redir_node(t_node *cmd, t_token *cur);
t_node	*parse(t_token *cur);
t_node *parse_left(t_token **cur);
void	parse_cmd(t_node *cmd, t_token **cur);
t_node	*new_node(t_token_type type, char *value);
void	lst_add_child(t_node *node, t_node *new);

void	print_tree(t_node *root);

// EXIT
void	free_lexer(t_token **token);
void	free_pipeline(t_node **list);

#endif