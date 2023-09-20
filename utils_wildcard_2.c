/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:23:26 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/20 19:19:59 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_strjoin_wild(char const *s1, char const *s2)
{
	char *res;
	size_t i;
	size_t total_len;
	size_t j;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + 2;
	res = malloc(total_len + 1);
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s1)){
		res[i] = s1[i];
		i++;
	}
	if (ft_strlen(s1) != 0)
	{
		res[i++] = ' ';
		res[i++] = ' ';
	}
	j = 0;
	while (j < ft_strlen(s2))
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

char *get_extension(const char *filename)
{
	char *dot = ft_strchr(filename, '.');
	if (!dot || dot == filename)
		return NULL;
	return dot + 1;
}

int select_case(t_data *shell_data, char *wildstring)
{
	int found_in_files = 0;
	int found_in_dirs = 0;
	int i = 0;

	while (shell_data->file_list[i] != NULL || shell_data->dir_list[i] != NULL)
	{
		if (!found_in_files && shell_data->file_list[i] != NULL && strcmp(shell_data->file_list[i], wildstring) == 0)
			found_in_files = 1;
		if (!found_in_dirs && shell_data->dir_list[i] != NULL && strcmp(shell_data->dir_list[i], wildstring) == 0)
			found_in_dirs = 1;
		if (found_in_files && found_in_dirs)
			return 2;
		i++;
	}

	if (found_in_files)
	{
		return 0;
	}
	else if (found_in_dirs)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
