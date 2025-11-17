/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 20:11:26 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/15 20:15:34 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.c"

t_token *new_token(t_token_type type, char *value)
{
	t_token *t = malloc(sizeof(t_token));
	if (!t)
		return (NULL);
	t->type = type;
	t->value = value;
	t->next = (NULL);
	return t;
}

void token_add_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
