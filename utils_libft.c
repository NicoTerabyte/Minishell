/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:51:50 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/01 17:38:49 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_matrix(char **s)
{
	int i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (0);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	if (i < n && src[i] == '\0')
	{
		while (dest[i] != '\0')
		{
			dest[i] = '\0';
			++i;
		}
	}
	return (dest);
}


char *ft_strcat(char *dest, char *src)
{
	int i;
	int j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	ft_strncat(char **dest, char c, int nb)
{
    // Calcola la lunghezza attuale della stringa
    size_t current_len = strlen(*dest);

    // Rialloca la memoria per includere il nuovo carattere e il terminatore nullo
    *dest = (char *)realloc(*dest, current_len + nb + 1);

    if (*dest == NULL) {
        // Gestione dell'errore di riallocazione della memoria
        fprintf(stderr, "Errore di riallocazione di memoria\n");
        exit(1);
    }

    // Aggiunge il carattere alla fine della stringa utilizzando un ciclo while
    int i = 0;
    while (i < nb) {
        (*dest)[current_len + i] = c;
        i++;
    }

    // Aggiunge il terminatore nullo alla fine della stringa
    (*dest)[current_len + nb] = '\0';
}
