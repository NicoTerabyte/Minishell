/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:41:27 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/10 15:09:34 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

// void	ft_bzero(void *s, size_t n);
// void	*ft_memcpy(void *dst, const void *src, int n);
// void	*ft_calloc(int count, int size);
char	*get_next_line(int fd);
// int		ft_strlen(char *str);

#endif
