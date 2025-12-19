/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/17 15:09:42 by jderachi          #+#    #+#             */
/*   Updated: 2025/12/17 16:14:21 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>	

int	builtin_env(t_env *env)
{
	int	i;

	i = 1;
	while (env)
    {
        printf("%s=%s\n", env->variable, env->value);
        env = env->next;
    }
    return (0);
}
