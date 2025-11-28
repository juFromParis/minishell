/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:33:36 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/28 13:33:24 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h" 

int	is_error_pipe(t_node *node)
{
	if (!node)
		return (0);
	if (strcmp(node->value, "||") == 0
		&& (!node->sibling || !node->previous || node->sibling->type == END))
	{
		printf("bash: syntax error near unexpected token `||'\n");
		return (1);
	}
	if (strcmp(node->value, "|") == 0
		&& (!node->sibling || !node->previous || node->sibling->type == END))
	{
		printf("bash: syntax error near unexpected token `|'\n");
		return (1);
	}
	return (0);
}










