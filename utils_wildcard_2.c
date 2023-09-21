/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:23:26 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/21 13:26:37 by abuonomo         ###   ########.fr       */
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

char *create_path(char *directory)
{
	char *path;
	path = current_dir();
	ft_strcat(path, "/"); // Aggiungi uno slash
    ft_strcat(path,directory);
	return (path);
}
