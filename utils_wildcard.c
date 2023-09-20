/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:52:51 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/19 21:38:45 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_wildcard(char *input)
{
	while (*input)
	{
		if (*input == '*')
			return (1);
		input++;
	}
	return (0);
}

char *current_dir(void)
{
	char *cd;

	cd = malloc(1024 * sizeof(char));
	if (getcwd(cd, 1024) == NULL)
		perror("Errore ottenimento del percorso");
	return (cd);
}

int matrix_dimension(t_data *shell_data, int flag)
{
	DIR *dir;
	struct dirent *entry;
	int count;

	count = 0;
	dir = opendir(current_dir());
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (flag == 1)
		{
			if (entry->d_type == DT_DIR)
				count++;
		}
		else
			count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

char **matrix_directory(t_data *shell_data)
{
	int rows;
	char **dir_matrix;
	struct dirent *entry;
	DIR *dir;

	dir = opendir(current_dir());
	if (!dir)
		return NULL;
	rows = matrix_dimension(shell_data, 1);
	dir_matrix = (char **)malloc((rows + 1) * sizeof(char *));
	rows = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_DIR)
		{
			dir_matrix[rows] = ft_strdup(entry->d_name);
			rows++;
		}
		entry = readdir(dir);
	}
	dir_matrix[rows] = NULL;
	closedir(dir);
	return (dir_matrix);
}

char **matrix_file(t_data *shell_data)
{
	int rows;
	char **dir_matrix;
	struct dirent *entry;
	DIR *dir;

	shell_data->dir_list = matrix_directory(shell_data);
	dir = opendir(current_dir());
	if (!dir)
		return NULL;
	rows = matrix_dimension(shell_data, 0);
	dir_matrix = (char **)malloc((rows + 1) * sizeof(char *));
	rows = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		if (entry->d_type == DT_REG)
		{
			dir_matrix[rows] = ft_strdup(entry->d_name);
			rows++;
		}
		entry = readdir(dir);
	}
	dir_matrix[rows] = NULL;
	closedir(dir);
	return (dir_matrix);
}
