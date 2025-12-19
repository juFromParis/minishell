/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtaniga <vtaniga@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 13:02:42 by vtaniga           #+#    #+#             */
/*   Updated: 2025/12/15 14:20:04 by vtaniga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H
# include <dirent.h>
# include <stdio.h>

typedef struct s_env	t_env;
char					**init_entries(char **dir_entries, DIR *d,
							struct dirent *dir);
int						filter_entries_start(char **entries, char *rmv);
int						filter_entries_end(char **entries, char *rmv);
int						filter_entries(char **entries, const char *rmv);
void					free_split(char **split);
int						count_dir_entries(void);
char					**get_directory_entries(void);
int						parse_pattern(char *pattern, int *start_flag,
							int *end_flag);
char					**apply_pattern_filters(char **entries,
							char **split_pattern, int start_flag, int end_flag);
char					**safe_malloc_entries(int count);
void					init_helper(int err, DIR *d);
char					**wildcard_expand(char *pattern);
char					*get_variable_name(const char *str, int *len);
char					*replace_variable(char *str, t_env *env);
char					*dollar_scanner(char *str);
char					**wildcard_expand(char *pattern);
char					*safe_str_replace(char *original, char *dollar_pos,
							char *var_name, char *env_value);
char					*replace_variable(char *str, t_env *env);
char					*expand_variables(char *input, t_env *env_list);
#endif