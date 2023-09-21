/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:23:26 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/21 15:45:17 by abuonomo         ###   ########.fr       */
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

char *directory_manager(char *directory,int flag)
{
	int rows;
	char **matrix;
	struct dirent *entry;
	DIR *dir;

	dir = opendir(create_path());
	if (!dir)
		return NULL;
	rows = matrix_dimension(0,dir);
	matrix = (char **)malloc((rows + 1) * sizeof(char *));
	rows = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
			matrix[rows] = ft_strdup(entry->d_name);
			rows++;
			entry = readdir(dir);
	}
	matrix[rows] = NULL;
	closedir(dir);
	sort_string_matrix(matrix, rows);
	if(flag = 1)
		return print_file();  //da scrivere
	return print_name_file(); //da scrivere
}
