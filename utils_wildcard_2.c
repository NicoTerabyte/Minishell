/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_wildcard_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 17:23:26 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/14 16:28:45 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mcharnum(char **matrice)
{
	int	lenght;
	int	num_s;
	int	i;

	lenght = 0;
	num_s = 0;
	i = 0;
	printf("%s",matrice[i]);
	while (matrice[i] != NULL)
	{
		lenght += strlen(matrice[i]);
		num_s++;
		i++;
	}
	lenght += 2 * (num_s - 1);
	return (lenght);
}

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
	res[i++] = ' ';
	res[i++] = ' ';
	j = 0;
	while (j < ft_strlen(s2))
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}
