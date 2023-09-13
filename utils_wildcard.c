/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:52:51 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/13 15:01:25 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_wildcard(char *input)
{
	while(*input){
		if(*input == '*')
			return 1;
		input++;
	}
	return 0;
}

int matrix_dimension(t_data *shell_data)
{

	DIR *dir = opendir(shell_data->copy_env[21]);
	struct dirent *entry;
	int count;
	if (dir == NULL) {
		perror("opendir() error");
		return 1;
	}
	while ((entry = readdir(dir)) != NULL)
			count++;
	return count;
	closedir(dir);
}

void stampaMatriceChar(char** matrice) {
    for (int i = 0; matrice[i] != NULL; i++) {
        for (int j = 0; matrice[i][j] != '\0'; j++) {
            printf("%c ", matrice[i][j]);
        }
        printf("\n");
    }
}


char **matrix_dir(t_data *shell_data)
{
	int		rows;
	char	**dir_matrix;
	struct	dirent *entry;
	DIR		*dir;
	dir = opendir(shell_data->copy_env[21]);
	rows = matrix_dimension(shell_data);
	dir_matrix = (char **) malloc(rows*sizeof(char *));
	rows = 0;
	if (dir == NULL) {
		perror("opendir() error");
		return 1;
	}
	while ((entry = readdir(dir)) != NULL)
		dir_matrix[rows++][0] = entry->d_name;
	stampaMatriceChar(dir_matrix);
	closedir(dir);
	return dir_matrix;
}


