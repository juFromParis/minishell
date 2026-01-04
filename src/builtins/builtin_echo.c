/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:09:58 by jderachi          #+#    #+#             */
/*   Updated: 2026/01/04 13:11:46 by jderachi         ###   ########.fr       */
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
		ft_putstr_fd(word, 1);
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
		ft_putstr_fd(value, 1);
	ft_putstr_fd(word + pos, 1);
	free(var);
}

int	builtin_echo(t_node *node, t_env *env)
{
	//ft_putstr_fd("ECHO->FD1\n", 1);
	//ft_putstr_fd("ECHO->FD2\n", 2);
	int		i;
	char	**argv;

	(void)env;

	if (!node)
		return (0);

	argv = NULL;
	if (node->cmd && node->cmd[0])
		argv = node->cmd;
	else if (node->cmd2 && node->cmd2[0])
		argv = node->cmd2;
	if (!argv)
		return (0);

	i = 1;
	while (argv[i])
	{
		if (i > 1)
			ft_putchar_fd(' ', 1);
		ft_putstr_fd(argv[i], 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
	return (0);
}


// int	builtin_echo(t_node *node, t_env *env)
// {
// 	int		i;
// 	int		j;
// 	char	**array;
// 	char	**argv;

// 	argv = NULL;
// 	if (node->cmd && node->cmd[0])
// 		argv = node->cmd;
// 	else if (node->cmd2 && node->cmd2[0])
// 		argv = node->cmd2;
// 	if (!argv)
// 		return (0);

// 	i = 1;
// 	while (argv[i])
// 	{
// 		array = ft_split(argv[i], ' ');
// 		j = 0;
// 		while (array[j])
// 		{
// 			if (i > 1 || j > 0)
// 				ft_putchar_fd(' ', 1);
// 			echo_print_word(array[j], env);
// 			j++;
// 		}
// 		free_array(array);
// 		i++;
// 	}
// 	ft_putchar_fd('\n', 1);
// 	return (0);
// }

