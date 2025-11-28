/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ischeck.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:59:06 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/28 13:43:01 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_issign(char c)
{
	if (c == '|'
		|| c == '<'
		|| c == '>'
		|| c == '&'
		|| c == '('
		|| c == ')')
		return (1);
	return (0);
}

int	ft_isoperator(t_token_type type)
{
	if (type == OPE || type == PIPE || type == AND || type == OR)
		return (1);
	return (0);
}

int	ft_isredir(char *str)
{
	if (!str)
		return (0);
	if (ft_strcmp(str, ">") == 0
		|| ft_strcmp(str, "<") == 0
		|| ft_strcmp(str, ">>") == 0
		|| ft_strcmp(str, "<<") == 0)
		return (1);
	return (0);
}

int	ft_isbuiltin(t_token_type type)
{
	if (type == FCT
		|| type == ECHO
		|| type == CD
		|| type == PWD
		|| type == EXPORT
		|| type == UNSET
		|| type == ENV
		|| type == EXIT)
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}
