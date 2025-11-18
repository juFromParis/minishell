/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:24:05 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/18 20:15:27 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_redir(t_token_type type)
{
	if (type == T_REDIR_IN
		|| type == T_REDIR_OUT
		|| type == T_HEREDOC
		|| type == T_APPEND)
		return (1);
	return (0);
}

t_node *parse_left(t_token **cur)
{
    t_node *cmd;
    t_node *word;

    if (!cur || !*cur)
        return NULL;

    cmd = new_node(N_CMD, NULL);
    if (!cmd)
        return NULL;

    while (*cur && (*cur)->type != T_PIPE)
    {
        if ((*cur)->type == T_WORD)
        {
            word = new_node(N_WORD, (*cur)->value);
            lst_add_child(cmd, word);
        }
        /* sinon : redirections, quotes, etc.
           Tu peux les ignorer pour l’instant */

        *cur = (*cur)->next; // AVANCER dans les tokens !!!
    }
    return cmd;
}

t_node	*parse(t_token *cur)
{
	t_node	*pipeline;
	t_node	*cmd_left;

	if (!cur)
		return (NULL);
	pipeline = new_node(N_START, NULL);
	if (!pipeline)
		return (NULL);
	while (cur)
	{
		cmd_left = parse_left(&cur);
		lst_add_child(pipeline, cmd_left);
		if (cur && cur->type == T_PIPE)
			cur = cur->next;
	}
	return (pipeline);
}
