/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 17:52:51 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/14 16:31:53 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_wildcard(char *input)
{
	while (*input)
	{
		if (*input == '*')
			return (1);
		input++;
	}
	return (0);
}

char	*current_dir(void)
{
	char	*cd;

	cd = malloc(1024 * sizeof(char));
	if (getcwd(cd, 1024) == NULL)
		perror("Errore ottenimento del percorso");
	return (cd);
}

int	matrix_dimension(t_data *shell_data)
{
	DIR				*dir;
	struct dirent	*entry;
	int				count;

	count = 0;
	dir = opendir(current_dir());
	entry = readdir(dir);
	while (entry != NULL)
	{
		entry = readdir(dir);
		count++;
	}
	closedir(dir);
	return (count);
}

char	**matrix_dir(t_data *shell_data)
{
	int				rows;
	char			**dir_matrix;
	struct dirent	*entry;
	DIR				*dir;

	dir = opendir(current_dir());
	rows = matrix_dimension(shell_data);
	dir_matrix = (char **) malloc((rows + 1) * sizeof(char *));
	rows = 0;
	entry = readdir(dir);
	while (entry != NULL)
	{
		entry = readdir(dir);
		dir_matrix[rows++] = entry->d_name;
	}
	dir_matrix[rows] = 0;
	closedir(dir);
	return (dir_matrix);
}
