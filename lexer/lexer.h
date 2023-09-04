/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:54:57 by alessiolong       #+#    #+#             */
/*   Updated: 2023/09/04 17:19:06 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# define START 0
# define ADD 1
# define LIST 2
# define GET 3
# include "../libft/libft.h"
# include "../tokenizer/tokenizer.h"
# include "../global.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

void	*handle_list_heredocs(int op);
void	handle_here_doc(char *del);
int		count_syntax(char *str);
int		ft_isspace(char c);
char	*fix_white_spaces(char *str);
char	*fix_syntax(char *str);

int check(char *s);
int check_parentheses(char *s, int *i);
int check_number(char *s);
int check_quote(char *s);
int check_operator(char *s, int *i);
int check_redirection(char *s, int *i);

#endif
