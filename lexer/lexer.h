/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:54:57 by alessiolong       #+#    #+#             */
/*   Updated: 2023/09/02 17:45:42 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# define START 0
# define ADD 1
# define LIST 2
# define GET 3
# include "../libft/libft.h"

void	*handle_list_heredocs(int op);

#endif
