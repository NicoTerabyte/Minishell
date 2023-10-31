/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:35:53 by mlongo            #+#    #+#             */
/*   Updated: 2023/10/31 17:49:49 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

typedef struct s_mini
{
	char	**env;
} t_mini;


# include <time.h>
# include <sys/wait.h>
# include "global.h"
# include "./lexer/lexer.h"
# include "./libft/libft.h"
# include "./tokenizer/tokenizer.h"
# include "./tree/tree.h"
# include "./executor/executor.h"
# include "./builtins/builtins.h"
# include "./gnl/get_next_line_bonus.h"
# include "./expander/expander.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>

# define SET 10
# define GET_TREE 11
# define GET_TOKENS 12


void	env_container(int action, void *arg, t_mini *the_copy);
void	signal_handler(int signum);
void	ign(int signum);
void	*var_container(t_token *token_lst, t_tree *tree, int op);
void	ft_free_all(t_token *token_lst, t_tree *tree);
void	free_tree(t_tree *tree);
void	free_tokens(t_token *token_lst);
void	printTree(t_tree *node, int level, char *message);

#endif
