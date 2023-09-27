/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_mini_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 21:54:06 by lnicoter          #+#    #+#             */
/*   Updated: 2023/09/24 21:55:08 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
