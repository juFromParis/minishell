/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:16:51 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/28 13:48:14 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

t_token	*check_operator(char *str, int *i)
{
	if (str[*i] == '<' && str[*i + 1] == '<')
		return ((*i) = (*i) + 2, new_token(RDR, ft_strdup("<<")));
	else if (str[*i] == '<')
		return ((*i)++, new_token(RDR, ft_strdup("<")));
	else if (str[*i] == '>' && str[*i + 1] == '>')
		return ((*i) = (*i) + 2, new_token(RDR, ft_strdup(">>")));
	else if (str[*i] == '>')
		return ((*i)++, new_token(RDR, ft_strdup(">")));
	else if (str[*i] == '&' && str[*i + 1] == '&')
		return ((*i) = (*i) + 2, new_token(OPE, ft_strdup("&&")));
	else if (str[*i] == '|' && str[*i + 1] == '|')
		return ((*i) = (*i) + 2, new_token(OPE, ft_strdup("||")));
	else if (str[*i] == '|')
		return ((*i)++, new_token(OPE, ft_strdup("|")));
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
		&& !ft_issign(str[*i]))
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
	return (new_token(lex_builtin(word_str), word_str));
}

t_token_type	lex_builtin(char *value)
{
	if (ft_strcmp(value, "echo") == 0)
		return (ECHO);
	else if (ft_strcmp(value, "cd") == 0)
		return (CD);
	else if (ft_strcmp(value, "pwd") == 0)
		return (PWD);
	else if (ft_strcmp(value, "export") == 0)
		return (EXPORT);
	else if (ft_strcmp(value, "unset") == 0)
		return (UNSET);
	else if (ft_strcmp(value, "env") == 0)
		return (ENV);
	else if (ft_strcmp(value, "exit") == 0)
		return (EXIT);
	else
		return (WORD);
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
		if (ft_issign(str[i]))
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
	free(str);
	return (token_list);
}
