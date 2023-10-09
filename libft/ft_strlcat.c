/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 19:17:09 by mlongo            #+#    #+#             */
/*   Updated: 2023/10/09 22:18:27 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	int		lenght;
	size_t	dstlen;
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	lenght = ft_strlen(src) + ft_strlen(dst);
	dstlen = ft_strlen(dst);
	i = 0;
	while (src[i] && i + dstlen < size - 1)
	{
		dst[i + dstlen] = src[i];
		i++;
	}
	if (dstlen < size)
		dst[i + dstlen] = 0;
	else
		return (ft_strlen(src) + size);
	return (lenght);
}

void	ft_strcat(char *dst, const char *src)
{
	int		i;
	int		size;

	size = ft_strlen(dst);
	i = 0;

	while (src[i])
	{
		printf("processo %c\n", src[i]);
		dst[size + i] = src[i];
		i++;
	}
	dst[size + i] = '\0';
}
