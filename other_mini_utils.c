/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_mini_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:54:06 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/06 17:50:09 by lnicoter         ###   ########.fr       */
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

char	**split_bt_nt_t_mc(char *str, char c)
{
	char	**matrix;
	int		i;
	int		j;

	j = -1;
	i = -1;
	matrix = malloc(3 * sizeof(char *) + 1);
	while (++i < 3)
		matrix[i] = NULL;
	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
		{
			matrix[0] = ft_substr(str, 0, i);
			matrix[1] = malloc((strlen(str) + 1) * sizeof(char));
			i++;
			while (str[i])
			{
				matrix[1][++j] = str[i];
				i++;
			}
			matrix[1][++j] = '\0';
			break ;
		}
	}
	matrix[2] = 0; //da sistemare pensa assai
	return (matrix);
}
