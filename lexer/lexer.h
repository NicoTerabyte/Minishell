/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:54:57 by alessiolong       #+#    #+#             */
/*   Updated: 2023/11/08 19:00:19 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
#define LEXER_H

# define START 0
# define ADD 1
# define LIST 2
# define GET 3

# include "../minishell.h"

void	*handle_list_heredocs(int op);
void	handle_here_doc(char *del, t_mini *mini);
int		count_syntax(char *str);
int		ft_isspace(char c);
char	*fix_white_spaces(char *str);
char	*fix_syntax(char *str);
int		check(char *s, t_mini *mini);
int		check_parentheses(char *s, int *i);
int		check_number(char *s);
int		check_number_back(char *s, char *start);
int		check_back(char *s, int i);
int		check_quote(char *s);
int		check_operator(char *s, int *i);
int		not_op(char *c);
int		is_one_char(char *c);
int		is_two_char(char *c);
int		is_double(char *s, int *i);
void	del(void *str);
#endif
