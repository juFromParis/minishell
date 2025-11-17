/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 09:42:56 by jderachi          #+#    #+#             */
/*   Updated: 2025/11/17 10:31:50 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*dest;

	i = 0;
	len = 0;
	while (src[len])
		len++;
	dest = (char *)malloc(sizeof(char) * len + 1);
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


char *ft_strndup(const char *s, size_t n)
{
    size_t len = 0;
    char *dup;

    while (s[len] && len < n)
        len++;

    dup = malloc(len + 1);
    if (!dup)
        return NULL;

    for (size_t i = 0; i < len; i++)
        dup[i] = s[i];

    dup[len] = '\0';
    return dup;
}