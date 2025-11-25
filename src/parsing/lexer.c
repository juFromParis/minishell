/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:16:51 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/25 12:28:06 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

t_token	*check_operator(char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
		return ((*i) = (*i) + 2, new_token(HEREDOC, ft_strdup("<<")));
	else if (str[*i] == '<')
		return ((*i)++, new_token(REDIR_IN, ft_strdup("<")));
	else if (str[*i] == '>' && str[*i + 1] == '>')
		return ((*i) = (*i) + 2, new_token(APPEND, ft_strdup(">>")));
	else if (str[*i] == '>')
		return ((*i)++, new_token(REDIR_OUT, ft_strdup(">")));
	else if (str[*i] == '&' && str[*i + 1] == '&')
		return ((*i) = (*i) + 2, new_token(AND, ft_strdup("&&")));
	else if (str[*i] == '|' && str[*i + 1] == '|')
		return ((*i) = (*i) + 2, new_token(OR, ft_strdup("||")));
	else if (str[*i] == '|')
		return ((*i)++, new_token(PIPE, ft_strdup("|")));
	else if (str[*i] == '(')
		return ((*i)++, new_token(PARENT_OPEN, ft_strdup("(")));
	else if (str[*i] == ')')
		return ((*i)++, new_token(PARENT_CLOSE, ft_strdup(")")));
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
		&& !ft_isspace(str[*i])
		&& !ft_isoperator(str[*i]))
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
	return (new_token(WORD, word_str));
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
		while (ft_isspace(str[i]))
			i++;
		if (ft_isoperator(str[i]))
		{
			token = check_operator(str, &i);
			token_push(&token_list, token, &i);
		}
		else
		{
			token = check_word(str, &i);
			token_push(&token_list, token, &i);
		}
	}
	token_add_back(&token_list, new_token(END, NULL));
	return (token_list);
}
