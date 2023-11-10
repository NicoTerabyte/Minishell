/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_mini_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:54:06 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/10 16:38:32 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_mat(char **str1, char **str2)
{
	char	*temp;

	temp = *str1;
	*str1 = *str2;
	*str2 = temp;
}

char	*ft_strndup(char *str, int start, int finish)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_calloc((finish - start) + 1, 1);
	while (start < finish)
	{
		ret[i] = str[start];
		i ++ ;
		start ++;
	}
	ret[i] = 0;
	return (ret);
}
