/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:16:51 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/16 19:00:13 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_token	*new_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->value = value;
	token->next = NULL;
	return (token);
}

t_token	*check_operator(char *tmp, int *i)
{
	if (tmp[*i] == '<')
	{
		if (tmp[*i + 1] == '<')
		{
			(*i)++;
			return (new_token(T_HEREDOC, ft_strdup("<<")));
		}
		(*i)++;
		return (new_token(T_REDIR_IN, ft_strdup("<")));
	}
	if (tmp[*i] == '>')
	{
		if (tmp[*i + 1] == '>')
		{
			(*i)++;
			return (new_token(T_APPEND, ft_strdup(">>")));
		}
		(*i)++;
		return (new_token(T_REDIR_OUT, ft_strdup(">")));
	}
	if (tmp[*i + 1] == '|')
	{
		(*i)++;
		return (new_token(T_PIPE, ft_strdup("|")));
	}
}

t_token	*parse(char *str)
{
	t_token	*token_list;
	t_token	*token;
	char	*word;
	int		i;

	token_list = NULL;
	i = 0;
	while (str[i])
	{
		while (isspace(str[i]))
			i++;
		if (!str[i])
			break ;
		if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		{
			token = check_operator(str, &i);
			token_add_back(&token_list, token);
			continue ;
		}
		word = check_word(str, &i);
		token_add_back(&token_list, new_token(T_WORD, word));
	}
	token_add_back(&token_list, new_token(T_END, NULL));
	return (token_list);
}
