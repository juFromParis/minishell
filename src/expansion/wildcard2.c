/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 11:43:03 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 11:49:20 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../exec/exec.h"
#include "../utils/utils.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int	count_dir_entries(void)
{
	DIR				*d;
	struct dirent	*dir;
	int				count;

	count = 0;
	d = opendir(".");
	dir = readdir(d);
	if (!d)
	{
		perror("opendir");
		exit(1);
	}
	errno = 0;
	while (dir != NULL)
	{
		count++;
	}
	if (errno != 0)
	{
		perror("readdir");
		closedir(d);
		exit(1);
	}
	closedir(d);
	return (count);
}

char	**safe_malloc_entries(int count)
{
	char	**dir_entries;

	dir_entries = malloc(sizeof(char *) * (count + 1));
	if (!dir_entries)
	{
		perror("malloc");
		exit(1);
	}
	dir_entries[count] = NULL;
	return (dir_entries);
}

void	init_helper(int err, DIR *d)
{
	if (err != 0)
	{
		perror("readdir");
		closedir(d);
		exit(1);
	}
}

char	**init_entries(char **dir_entries, DIR *d, struct dirent *dir)
{
	int	index;

	index = 0;
	d = opendir(".");
	dir = readdir(d);
	if (!d)
		perror("opendir");
	if (!d)
		exit(1);
	errno = 0;
	while (dir != NULL)
	{
		dir_entries[index] = malloc(sizeof(char) * (ft_strlen(dir->d_name)
					+ 1));
		if (!dir_entries[index])
		{
			perror("malloc");
			while (index > 0)
				free(dir_entries[index]);
			exit(1);
		}
		ft_strcpy(dir_entries[index], dir->d_name);
		index++;
	}
	return (init_helper(errno, d), closedir(d), dir_entries);
}
