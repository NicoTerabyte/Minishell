/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:47:11 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/09 12:37:49 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "../minishell.h"



t_token	*tokenizer(char **splitcmd, t_mini *mini);
int		free_matrix(char **s);
void	scan_parenthesis(char **splitcmd, int *i, t_token **token_lst);
void	scan_redirections(char **splitcmd, int *i, t_token **token_lst, t_mini *mini);
void	scan_env_decl(char **splitcmd, int *i, t_token **token_lst, t_mini *mini);
void	scan_cmd(char **splitcmd, int *i, t_token **token_lst, t_mini *mini);
void	scan_operator(char **splitcmd, int *i, t_token **token_lst);
int		verify_env_decl(char **splitcmd, int *i);
void	tok_add_back(t_token **lst, t_token *new);
char	*ft_strpbrk(char *str, char *set);
int		ft_isspace(char c);
int		ft_stralnum(char *str);
char	*ft_strbash_control(char *str);
char	*ft_strbash_control_args(char *str);
void	print_tokens(t_token *token_lst);
void	initializePrevious(t_token *head);
void	*unlink_here_docs(t_list *here_docs_lst);
char	*here_doc_name();

#endif
