/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:18:01 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/18 19:10:32 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_lexer(t_token **list)
{
	t_token	*tmp;
	t_token	*current;

	current = *list;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*list = NULL;
}
