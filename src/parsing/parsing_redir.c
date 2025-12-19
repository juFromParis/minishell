/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/05 11:35:42 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/17 16:02:34 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_operator_char(char c)
{
	return (c == '<' || c == '>');
}

int	count_tokens(const char *s)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		if (isspace(s[i]))
			i++;
		else if (is_operator_char(s[i]))
		{
			count++;
			if (s[i + 1] == s[i])
				i += 2;
			else
				i++;
		}
		else
		{
			count++;
			while (s[i] && !isspace(s[i]) && !is_operator_char(s[i]))
				i++;
		}
	}
	return (count);
}

// static char	*extract_operator(const char *s, int *i)
// {
// 	char	*op;

// 	if (s[*i + 1] == s[*i])
// 	{
// 		op = ft_strncpy(s, *i, 2);
// 		*i += 2;
// 	}
// 	else
// 	{
// 		op = ft_strncpy(s, *i, 1);
// 		*i += 1;
// 	}
// 	return (op);
// }

// static char	*extract_word(const char *s, int *i)
// {
// 	int	start;

// 	start = *i;
// 	while (s[*i] && !ft_isspace(s[*i]) && !is_operator_char(s[*i]))
// 		(*i)++;
// 	return (ft_strncpy(s, start, *i - start));
// }

// char **split_for_redir(const char *s)
// {
//     char    **args;
//     char    buffer[4096];
//     int     i = 0, j = 0, k;
//     char    quote = 0;

//     args = malloc(sizeof(char *) * (ft_strlen(s) + 1));
//     if (!args)
//         return NULL;

//     while (s[i])
//     {
//         while (s[i] == ' ')
//             i++;
//         if (!s[i])
//             break;

//         k = 0;
//         quote = 0;
//         while (s[i])
//         {
//             if ((s[i] == '"' || s[i] == '\''))
//             {
//                 if (!quote)
//                     quote = s[i];
//                 else if (quote == s[i])
//                     quote = 0;
//                 i++;
//                 continue;
//             }
//             if (s[i] == ' ' && !quote)
//                 break;
//             buffer[k++] = s[i++];
//         }
//         buffer[k] = '\0';
//         args[j++] = ft_strdup(buffer);
//     }
//     args[j] = NULL;
//     return args;
// }

char **split_for_redir(const char *s)
{
    char    **args;
    char    buffer[4096];
    int     i = 0, j = 0, k;
    char    quote = 0;

    args = malloc(sizeof(char *) * (ft_strlen(s) + 1));
    if (!args)
        return NULL;

    while (s[i])
    {
        while (s[i] == ' ')
            i++;
        if (!s[i])
            break;

        k = 0;
        quote = 0;
        while (s[i])
        {
            if ((s[i] == '"' || s[i] == '\''))
            {
                if (!quote)
                    quote = s[i];
                else if (quote == s[i])
                    quote = 0;
                i++;
                continue;
            }
            if (s[i] == ' ' && !quote)
                break;
            buffer[k++] = s[i++];
        }
        buffer[k] = '\0';
        args[j++] = ft_strdup(buffer);
    }
    args[j] = NULL;
    return args;
}
