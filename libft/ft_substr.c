/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:18:07 by mlongo            #+#    #+#             */
/*   Updated: 2023/09/15 19:20:50 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "libft.h"
#include <stdio.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		str = ft_strdup("");
	else if (len < ft_strlen(s) - start)
		str = (char *) malloc(sizeof(*s) * (len + 1));
	else
		str = (char *) malloc(sizeof(*s) * (ft_strlen(s) - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (i >= start && j < len)
			str[j++] = s[i];
		i++;
	}
	str[j] = 0;
	printf("il piu importante dei return %s\n", str);
	return (str);
}
