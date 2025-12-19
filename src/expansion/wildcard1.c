/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/03 12:32:41 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 14:17:21 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../expansion/expansion.h"
#include "../utils/utils.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

char	**get_directory_entries(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			**entries;
	int				count;

	d = NULL;
	dir = NULL;
	count = count_dir_entries();
	entries = safe_malloc_entries(count);
	entries = init_entries(entries, d, dir);
	return (entries);
}

int	parse_pattern(char *pattern, int *start_flag, int *end_flag)
{
	if (!pattern)
		return (0);
	*start_flag = 0;
	*end_flag = 0;
	if (pattern[0] != '*')
		*start_flag = 1;
	if (pattern[ft_strlen(pattern) - 1] != '*')
		*end_flag = 1;
	return (1);
}

char	**apply_pattern_filters(char **entries, char **split_pattern,
		int start_flag, int end_flag)
{
	int	i;

	i = 0;
	while (split_pattern[i])
	{
		if (i == 0 && start_flag)
			filter_entries_start(entries, split_pattern[i]);
		else if (split_pattern[i + 1] == NULL && end_flag)
			filter_entries_end(entries, split_pattern[i]);
		else
			filter_entries(entries, split_pattern[i]);
		i++;
	}
	return (entries);
}

char	**wildcard_expand(char *pattern)
{
	char	**split_pattern;
	char	**entries;
	int		start_flag;
	int		end_flag;

	if (!pattern)
		return (NULL);
	start_flag = 0;
	end_flag = 0;
	entries = get_directory_entries();
	parse_pattern(pattern, &start_flag, &end_flag);
	split_pattern = ft_split(pattern, '*');
	if (!split_pattern)
	{
		free_split(entries);
		return (NULL);
	}
	entries = apply_pattern_filters(entries, split_pattern, start_flag,
			end_flag);
	free_split(split_pattern);
	return (entries);
}

// int	main(int argc, char **argv)
// {
// 	char	**entries;
// 	// char	*full_pattern;
// 	(void) argc;
// 	(void) argv;
// 	entries = wildcard_expand(argv[1]);
// 	if(!entries)
// 		return (1);
// 	print(entries);
// 	free_split(entries);
// 	return (0);
// }

// parameter expansion

// exit status expansion