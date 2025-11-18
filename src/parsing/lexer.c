/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:16:51 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/17 18:38:16 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

t_token	*check_operator(char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
	{
		(*i) = (*i) + 2;
		return (new_token(T_HEREDOC, ft_strdup("<<")));
	}
	else if (str[*i] == '<')
	{
		(*i)++;
		return (new_token(T_REDIR_IN, ft_strdup("<")));
	}
	else if (str[*i] == '>' && str[*i + 1] == '>')
	{
		(*i) = (*i) + 2;
		return (new_token(T_APPEND, ft_strdup(">>")));
	}
	else if (str[*i] == '>')
	{
		(*i)++;
		return (new_token(T_REDIR_OUT, ft_strdup(">")));
	}
	else if (str[*i] == '&' && str[*i + 1] == '&')
	{
		(*i) = (*i) + 2;
		return (new_token(T_AND, ft_strdup("&&")));
	}
	else if (str[*i] == '|' && str[*i + 1] == '|')
	{
		(*i) = (*i) + 2;
		return (new_token(T_OR, ft_strdup("||")));
	}
	else if (str[*i] == '|')
	{
		(*i)++;
		return (new_token(T_PIPE, ft_strdup("|")));
	}
	else if (str[*i] == '(')
	{
		(*i)++;
		return (new_token(T_PARENT_OPEN, ft_strdup("(")));
	}
	else if (str[*i] == ')')
	{
		(*i)++;
		return (new_token(T_PARENT_CLOSE, ft_strdup(")")));
	}
	return (NULL);
}

t_token	*check_word(char *str, int *i)
{
	int		start;
	int		len;
	char	*word_str;
	char	quote;

	start = *i;
	while (str[*i]
		&& !isspace(str[*i])
		&& str[*i] != '|'
		&& str[*i] != '<'
		&& str[*i] != '>'
		&& str[*i] != '&'
		&& str[*i] != '('
		&& str[*i] != ')')
	{
		if (str[*i] == '"' || str[*i] == '\'')
		{
			quote = str[*i];
			(*i)++;
			while (str[*i] && str[*i] != quote)
				(*i)++;
			if (str[*i] == quote)
				(*i)++;
		}
		else
			(*i)++;
	}
	len = *i - start;
	word_str = ft_strndup(str + start, len);
	return (new_token(T_WORD, word_str));
}

t_token	*lexer(char *str)
{
	t_token	*token_list;
	t_token	*token;
	int		i;

	token_list = NULL;
	i = 0;
	while (str[i])
	{
		while (isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		if (str[i] == '|'
			|| str[i] == '<'
			|| str[i] == '>'
			|| str[i] == '&'
			|| str[i] == '('
			|| str[i] == ')')
		{
			token = check_operator(str, &i);
			if (token != NULL)
				token_add_back(&token_list, token);
			else
				i++;
		}
		else
		{
			token = check_word(str, &i);
			if (token != NULL)
				token_add_back(&token_list, token);
			else
				i++;
		}
	}
	token_add_back(&token_list, new_token(T_END, NULL));
	return (token_list);
}
