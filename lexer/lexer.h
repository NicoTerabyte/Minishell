/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:54:57 by alessiolong       #+#    #+#             */
/*   Updated: 2023/11/06 17:19:26 by lnicoter         ###   ########.fr       */
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
void	handle_here_doc(char *del);
int		count_syntax(char *str);
int		ft_isspace(char c);
char	*fix_white_spaces(char *str);
char	*fix_syntax(char *str);

int	check(char *s);
int	check_parentheses(char *s, int *i);
int	check_number(char *s);
int	check_number_back(char *s, char *start);
int	check_back(char *s, int i);
int	check_quote(char *s);
int	check_operator(char *s, int *i);
// int	check_redirection(char *s, int *i);
int	not_op(char *c);
int is_one_char(char *c);
int is_two_char(char *c);
int is_double(char *s, int *i);

#endif
