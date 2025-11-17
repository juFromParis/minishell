/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:18:01 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/17 09:52:48 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_command(t_token **token)
{
	t_token	*tmp;
	t_token	*current;

	current = *token;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free(tmp);
	}
	*token = NULL;
}
