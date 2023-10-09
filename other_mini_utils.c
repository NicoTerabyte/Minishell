/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_mini_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:54:06 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/08 20:20:14 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	swap_mat(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

char	*ft_strndup(char *str, int start, int finish)
{
	int i;
	char *ret;

	i = 0;
	ret = ft_calloc((finish - start) + 1, 1);
	while(start < finish)
	{
		ret[i] = str[start];
		i ++ ;
		start ++;
	}
	ret[i] = 0;
	return(ret);
}

/*piano:
creare una funzione che prenda la stringa passata
e che la smembri in modo da riempire una matrice
con il nome della variabile evitando fino all =
(devo cancellare il primo = ovviamente) in seguito
un altra riga della matrice verrà riempito con ciò che viene dopo
l'= ok adesso che abbiamo chiarito bene cosa fare pensiamo ad un modo
per farlo, allora abbiamo una matrice da riempire questa matrice
di suo deve ricevere da 2 a massimo 3 valori (contando il carattere nullo)
perché noi guardiamo il nome della var e il suo valore ok chiaro
userò ft_strchr per capire se deve mallocare *2 o per 3
ovviamente nel primo caso */
char	**split_bt_nt_t_mc(char *str, char c)
{
	int		i;
	int		j;
	char	**mat;

	i = -1;
	j = -1;
	mat = (char **)malloc(3 * sizeof(char *));
	for (i = 0; i < 3; i++) {
		mat[i] = NULL;
	}
	if (ft_strchr(str, '=') != 0);
	{
		while(str[++i] != '=')
			;
		mat[0] = ft_substr(str, 0, i);
		mat[1] = ft_substr(str, i + 1, ft_strlen(str));
		mat[2] = NULL;
		return (mat);
	}
	if (ft_strchr(str, c) != 0)
	{
		mat[1] = ft_strdup(str);
		mat[2] = 0;
	}
	return (mat);
}


