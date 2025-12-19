/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 15:22:20 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/16 16:55:45 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../env/env.h"
#include "../inc/minishell.h"
#include "builtins.h"
#include <sys/wait.h>

int	builtin_cd(t_node *node, t_env *env)
{
	(void)node;
	(void)env;
	char *path;
	if(node->cmd && node->cmd[1])
		path = node->cmd[1];
	else if(node->cmd2 && node->cmd2[1])
		path = node->cmd2[1];
	// est ce qu'il faut rajouter des options ?
	//~/path ou ~user/path : extension combinée avec chemin relatif à la home.
	//- qui permet de revenir au repertoire precedent
	//~ qui permet d'aller dans le repertoire home
	// . et .. pour naviguer dans les repertoires
	// gestion des erreurs si le repertoire n'existe pas
	// gestion des permissions
	// gestion des liens symboliques
	// mise a jour des variables d'environnement PWD et OLDPWD
	// c'est une fonction qui change le repertoire courant
	// utilise la fonction chdir
	// retourne 0 en cas de succes, -1 en cas d'erreur
	//  = chdir(path);
	// if (ret == -1)
	// {
	// 	perror("cd");
	// 	return (-1);
	// }
	printf("------------------ debug start\n");
	printf("PWD: %s\n", get_env_value(env, "PWD"));
	printf("OLDPWD: %s\n", get_env_value(env, "OLDPWD"));
	set_env(&env, "OLDPWD", get_env_value(env, "PWD"));
	if(chdir(path) == -1)
	{
		perror("cd");
		return (-1);
	}
	set_env(&env, "PWD", getcwd(NULL, 0));
	update_prompt_env(&env);
	printf("cwd: %s\n", get_env_value(env, "PWD"));
	printf("------------------ debug end\n");
	return (0);
}
