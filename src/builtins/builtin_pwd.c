/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 14:04:27 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/17 14:05:56 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>

int	builtin_pwd(t_env *env)
{
	(void)env;
	printf("%s\n", get_env_value(env, "PWD"));
	return (0);
}
