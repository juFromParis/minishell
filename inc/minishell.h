/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 15:06:35 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/28 13:38:41 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\001\033[1;33m\002-minishell> \001\033[0m\002"
# define SYNTAX_ERROR "syntax error near unexpected token"

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
	OPE,
	WORD,
	PIPE,
	RDR,
	FCT,
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
	BUILTIN,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	END
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}	t_token;

typedef struct s_node
{
	t_token_type		type;
	char				*value;
	char				*file;
	struct s_node		*parent;
	struct s_node		*previous;
	struct s_node		*child;
	struct s_node		*sibling;
}	t_node;

// UTILS
int		ft_issign(char c);
int		ft_isoperator(t_token_type type);
int		ft_isspace(char c);
int		ft_isbuiltin(t_token_type type);
int		ft_isredir(char *str);
int		ft_strcmp(char *s1, char *s2);

char	*ft_strdup(char *src);
char	*ft_strndup(const char *s, size_t n);

// LEXER & PARSING
t_token	*lexer(char *str);
t_token	*new_token(t_token_type type, char *value);
t_token	*check_operator(char *str, int *i);
t_token	*check_word(char *str, int *i);

t_token_type	lex_builtin(char *value);

void	token_add_back(t_token **list, t_token *new);
void	token_push(t_token **list, t_token *token, int *i);
void	redir_node(t_node *cmd, t_token *cur);
void	parse_cmd(t_node *cmd, t_token **cur);
void	lst_add_child(t_node *node, t_node *new);

t_node	*parse(t_token *cur);
t_node	*parse_left(t_token **cur);
t_node	*new_node(t_token_type type, char *value);


// PARSE ERROR
int		is_parse_error(t_node *list);
int		is_error_ope(t_node *node);
int		is_error_redir(t_node *node);

void	print_tree(t_node *root);
void	print_lexer(t_token *token);

// EXIT
void	free_lexer(t_token **token);
void	free_pipeline(t_node **list);

#endif