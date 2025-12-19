/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jderachi <jderachi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:10:55 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/17 16:18:29 by jderachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

typedef struct s_node	t_node;
typedef struct s_env	t_env;
int	is_builtin_command(char *cmd);
int builtin_cd(t_node *node, t_env *env);
int	builtin_pwd(t_env *env);
int	builtin_echo(t_node *node, t_env *env);
int	builtin_env(t_env *env);
int	execute_builtin_command(t_node *node, t_env *env);
char *expand_var(char *str, t_env *env);

#endif