/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:52:51 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/21 20:25:34 by abuonomo         ###   ########.fr       */
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

int matrix_dimension(t_data *shell_data)
{
	struct dirent *entry;
	int count;
	DIR *dir;
	dir = opendir(current_dir());
	count = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		count++;
		entry = readdir(dir);
	}
	closedir(dir);
	return (count);
}

struct dirent **matrix_file(t_data *shell_data)
{
	int rows;
	struct dirent **dir_matrix;
	struct dirent *entry;
	DIR *dir;

	dir = opendir(current_dir());
	if (!dir)
		return NULL;
	rows = matrix_dimension(shell_data);
	dir_matrix = (struct dirent **)malloc((rows + 1) * sizeof(struct dirent *));
	rows = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		dir_matrix[rows] = entry;
		rows++;
		entry = readdir(dir);
	}
	dir_matrix[rows] = NULL;
	closedir(dir);
	return (dir_matrix);
}
