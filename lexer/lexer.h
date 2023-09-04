/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fla <fla@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 12:36:08 by fla               #+#    #+#             */
/*   Updated: 2023/09/03 07:18:12 by fla              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

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

// int	check_parentheses(char *str);
// int check_content(char *str, int i);
// int	check_quotes(char *str);
// int	check_operators(char *str);
// int check_back(char *str, int i, int n);

// char	*back_str(char *str, int i);
// char	*next_str(char *str, int i);


#endif