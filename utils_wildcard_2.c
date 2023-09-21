/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:23:26 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/21 18:19:47 by abuonomo         ###   ########.fr       */
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
	while (i < ft_strlen(s1))
	{
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

char *create_path(char *directory)
{
	char *path;
	path = current_dir();
	ft_strcat(path, "/"); // Aggiungi uno slash
	ft_strcat(path, directory);
	return (path);
}

char *print_file(char **matrix, int rows)
{
	int total_length;
	int i;
	char *result;
	int offset;

	i = 0;
	total_length = 0;
	offset = 0;
	while (i < rows)
	{
		total_length += ft_strlen(matrix[i]) + 1;
		i++;
	}
	result = (char *)malloc(total_length);
	if (result == NULL)
		return NULL;
	i = 0;
	while (i < rows)
	{
		offset += ft_strlcpy(result + offset, matrix[i], total_length - offset);
		result[offset] = '\n';
		offset++;
		i++;
	}
	if (rows > 0)
		result[offset - 1] = '\0';
	return result;
}

char *print_name_file(char **matrix, int rows, char *directory)
{
	int total_length = 0;
	int i = 0;
	int offset = 0;
	int j;
	char *result;

	while (i < rows)
	{
		total_length += strlen(matrix[i]) + strlen(directory) + 3;
		i++;
	}
	result = (char *)malloc(total_length + 1);
	if (result == NULL)
		return NULL;
	i = 0;
	offset = 0;
	strcpy(result, directory);
	offset = strlen(directory);
	result[offset] = ':';
	offset++;
	result[offset] = '\n';
	offset++;
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (matrix[i][j] != '\0')
		{
			result[offset] = matrix[i][j];
			offset++;
			j++;
		}
		result[offset] = '\n';
		offset++;
		i++;
	}
	if (rows > 0)
		result[offset - 1] = '\0';
	return result;
}
