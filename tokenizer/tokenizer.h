/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:47:11 by mlongo            #+#    #+#             */
/*   Updated: 2023/10/31 10:03:11 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

// # include "../libft/libft.h"
// # include "../gnl/get_next_line_bonus.h"
// # include "../lexer/lexer.h"
# include "../tree/tree.h"
# include "../minishell.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

typedef enum e_token_enum
{
	CMD_NAME,
	CMD_ARG,
	IN_FILE_TRUNC,
	HERE_DOC,
	OUT_FILE_TRUNC,
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
	char					*name;
	char					*value;
	struct	s_declaration	*next;
}	t_declaration;

typedef struct s_token
{
	t_token_enum	token;
	void			*value;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

// TOKENIZER

// command line adjusters

t_token	*tokenizer(char **splitcmd, t_mini *mini);
int		free_matrix(char **s);

//scanners

void	scan_parenthesis(char **splitcmd, int *i, t_token **token_lst);
void	scan_redirections(char **splitcmd, int *i, t_token **token_lst, t_mini *mini);
void	scan_env_decl(char **splitcmd, int *i, t_token **token_lst, t_mini *mini);
void	scan_cmd(char **splitcmd, int *i, t_token **token_lst, t_mini *mini);
void	scan_operator(char **splitcmd, int *i, t_token **token_lst);
int		verify_env_decl(char **splitcmd, int *i);

//utils

void	tok_add_back(t_token **lst, t_token *new);
char	*ft_strpbrk(char *str, char *set);
int		ft_isspace(char c);
int		ft_stralnum(char *str);
char	*ft_strbash_control(char *str);
void	print_tokens(t_token *token_lst);
void	initializePrevious(t_token *head);
void	*unlink_here_docs(t_list *here_docs_lst);
char	*here_doc_name();

#endif
