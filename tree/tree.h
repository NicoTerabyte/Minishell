/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:19:48 by mlongo            #+#    #+#             */
/*   Updated: 2023/10/31 11:01:30 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

// # include "../libft/libft.h"
// # include "../gnl/get_next_line_bonus.h"
// # include "../tokenizer/tokenizer.h"
# include "../minishell.h"
// # include <stdio.h>
// # include <stdlib.h>
// # include <unistd.h>
// # include <string.h>
// # include <readline/readline.h>
// # include <readline/history.h>
// # include <fcntl.h>

typedef enum e_tree_enum
{
	SIMPLE_CMD,
	OP,
	PARENTHESI,
}	t_tree_enum;

typedef struct s_cmd
{
	t_token *cmd_name;
	t_token *cmd_arg;
} t_cmd;

typedef struct s_simple_cmd
{
	t_token			*redir_list;
	struct s_cmd	*cmd;
	t_token			*env;
}	t_simple_cmd;

typedef struct s_tree
{
	t_tree_enum		type;
	void			*content;
	struct s_tree	*right;
	struct s_tree	*left;
	struct s_tree	*prev;
	char			**env;
}	t_tree;

typedef struct s_parenthesis
{
	t_token	*redir_list;
	t_tree	*tree;
}	t_parenthesis;


t_tree			*tree_create(t_token *token_lst, t_tree_enum calling);
t_parenthesis	*parenthesis_node(t_token *token_lst);
t_token			*parenthesis_redirections(t_token *token_lst);
t_token			*skip_par_tokens(t_token *token_lst);
int				verify_parenthesis(t_token *token_lst);
t_token			*skip_back_parenthesis(t_token *token_lst);
t_token			*skip_forward_parenthesis(t_token *token_lst);
t_token			*copy_tok(t_token *to_copy);
t_simple_cmd	*simple_cmd_redirections(t_token *token_lst);
void			simple_cmd(t_token *token_lst, t_simple_cmd *simple_cmd);
void			free_tokens(t_token *token_lst);

#endif
