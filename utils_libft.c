/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:51:50 by lnicoter          #+#    #+#             */
/*   Updated: 2023/08/24 18:31:17 by lnicoter         ###   ########.fr       */
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

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else if (s1[i] == '\0')
		return (-1);
	else if (s2[i] == '\0')
		return (1);
	else
		return (s1[i] - s2[i]);
}

