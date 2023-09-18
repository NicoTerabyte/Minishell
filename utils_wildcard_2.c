/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:23:26 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/18 18:56:18 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin_wild(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	total_len;
	size_t	j;

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
	if(ft_strlen(s1) != 0)
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


void stampaMatrice(char **matrice) {
    if (matrice == NULL) {
        printf("La matrice è vuota.\n");
        return;
    }
    char **ptr = matrice;
    while (*ptr != NULL) {
        char *riga = *ptr;
        while (*riga != '\0') {
            printf("%c", *riga);
            riga++;
        }
        printf("\n");
        ptr++;
    }
}

char *get_extension(const char *filename)
{
	char *dot = ft_strchr(filename, '.');
	if (!dot || dot == filename)
		return NULL;
	return dot + 1;
}
