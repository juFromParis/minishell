/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:58 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/17 17:07:02 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>

char	*extract_vars(const char *str)
{
	int	i;
	int	len;

	if (!str)
		return (NULL);

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (str[i] != '$')
		return (NULL);

	i++;
	len = 0;
	while (str[i + len] && (ft_isalnum(str[i + len]) || str[i + len] == '_'))
		len++;

	return (ft_substr(str, i, len));
}

void	echo_print_word(char *word, t_env *env)
{
	int		pos;
	char	*var;
	char	*value;

	var = extract_vars(word);
	if (!var)
	{
		printf("%s", word);
		return ;
	}
	value = get_env_value(env, var);
	pos = 0;
	while (word[pos] && word[pos] != '$')
		pos++;
	pos++;
	while (word[pos] && (ft_isalnum(word[pos]) || word[pos] == '_'))
		pos++;
	if (value)
		printf("%s", value);
	printf("%s", word + pos);
	free(var);
}

int	builtin_echo(t_node *node, t_env *env)
{
	int		i;
	int		j;
	char	**array;

	i = 1;
	while (node->cmd[i])
	{
		array = ft_split(node->cmd[i], ' ');
		j = 0;
		while (array[j])
		{
			if (i > 1 || j > 0)
				printf(" ");
			echo_print_word(array[j], env);
			j++;
		}
		free_array(array);
		i++;
	}
	printf("\n");
	return (0);
}
