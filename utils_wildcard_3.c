/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:23:26 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/21 13:27:07 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int select_case_fn(t_data *shell_data, char *wildstring)
{
	struct dirent *entry;
	DIR *dir;
	int count;

	count = 0;
	dir = opendir(current_dir());
	if (!dir)
		return NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			if(ft_strncmp(entry->d_name, wildstring, ft_strlen(wildstring)) == 0)
				count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

int select_case_pr(t_data *shell_data, char *wildstring)
{
	struct dirent *entry;
	DIR *dir;
	int count;

	count = 0;
	dir = opendir(current_dir());
	if (!dir)
		return NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			if(ft_strnstr(entry->d_name, wildstring, ft_strlen(entry->d_name)) != NULL)
				count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}


int select_case_ex(t_data *shell_data, char *wildstring)
{
	struct dirent *entry;
	DIR *dir;
	int count;

	count = 0;
	dir = opendir(current_dir());
	if (!dir)
		return NULL;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			if(ends_with(entry->d_name, wildstring))
				count++;
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

char *directory_manager(t_data *shell_data,char *directory,int flag)
{
	int rows;
	char **matrix;
	struct dirent *entry;
	DIR *dir;

	dir = opendir(create_path());
	if (!dir)
		return NULL;
	rows = matrix_dimension(shell_data, 1);
	matrix = (char **)malloc((rows + 1) * sizeof(char *));
	rows = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
			dir_matrix[rows] = ft_strdup(entry->d_name);
			rows++;
			entry = readdir(dir);
	}
	dir_matrix[rows] = NULL;
	closedir(dir);
	return (dir_matrix);
}
