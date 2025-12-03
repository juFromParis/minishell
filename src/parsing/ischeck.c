/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ischeck.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 11:59:06 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/03 18:55:10 by jderachi         ###   ########.fr       */
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
	if (type == T_PIPE || type == T_AND || type == T_OR)
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

/*
int	ft_isbuiltin(t_token_type type)
{
	if (type == T_FCT
		|| type == T_ECHO
		|| type == T_CD
		|| type == T_PWD
		|| type == T_EXPORT
		|| type == T_UNSET
		|| type == T_ENV
		|| type == T_EXIT)
		return (1);
	return (0);
}
*/

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}
