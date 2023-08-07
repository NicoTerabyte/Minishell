/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/07 18:22:40 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "./libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef enum e_token_enum
{
	CMD_NAME,
	CMD_ARG,
	IN_FILE_TRUNC,
	HERE_DOC,
	OUT_FILE_TRUN,
	OUT_FILE_APPEND,
	OPERATOR,
	ENV_VAR_DECL,
	ENV_VAR_UNSET,
	PARENTHESIS,
	NONE
}	t_token_enum;

typedef struct s_declaration
{
	int						concatenation;
	char					var_name;
	char					var_value;
	struct	s_declaration	*next;
	struct	s_declaration	*prev;
}	t_declaration;

typedef struct s_token
{
	t_token_enum	token;
	void			*value;
	struct s_token	*next;
}	t_token;

int		cmd_name(char *str);
t_token	*tokenizer(char **splitcmd);
int		count_syntax(char *str);
char	*fix_syntax(char *str);
int		free_matrix(char **s);
void	scan_parenthesis(char **splitwords, int *i, t_token **token_lst);
void	tok_add_back(t_token **lst, t_token *new);

#endif
