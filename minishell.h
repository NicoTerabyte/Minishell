/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:35:53 by mlongo            #+#    #+#             */
/*   Updated: 2023/10/13 19:15:07 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "global.h"
# include "./lexer/lexer.h"
# include "./libft/libft.h"
# include "./tokenizer/tokenizer.h"
# include "./tree/tree.h"
# include "./executor/executor.h"
# include "./builtins/builtins.h" 
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# define SET 10
# define GET_TREE 11
# define GET_TOKENS 12

char	**env_container(int action, void *arg);
void	signal_handler(int signum);
void	ign(int signum);
void	*var_container(t_token *token_lst, t_tree *tree, int op);
void	ft_free_all(t_token *token_lst, t_tree *tree);
void	free_tree(t_tree *tree);
void	free_tokens(t_token *token_lst);

#endif
