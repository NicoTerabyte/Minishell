/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_parenthesis.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:23:37 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/18 13:27:25 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"

int	verify_parenthesis(t_token *token_lst)
{
	while (token_lst->next && token_lst->token != OPERATOR)
	{
		if (token_lst->token == PARENTHESIS)
			return (1);
		token_lst = token_lst->next;
	}
	return (0);
}

t_token	*skip_par_tokens(t_token *token_lst)
{
	t_token	*new_token_lst;
	int		n_parenthesis;
	char	*value;

	n_parenthesis = 1;
	new_token_lst = NULL;
	token_lst = token_lst->next;
	while (token_lst && n_parenthesis)
	{
		if (token_lst->token == PARENTHESIS)
		{
			value = (char *)token_lst->value;
			if (ft_strncmp(value, "(", 1) == 0)
				n_parenthesis++;
			else
				n_parenthesis--;
		}
		if (n_parenthesis)
		{
			tok_add_back(&new_token_lst, copy_tok(token_lst));
			token_lst = token_lst->next;
		}
	}
	return (new_token_lst);
}

t_token	*parenthesis_redirections(t_token *token_lst)
{
	t_token	*redir_lst;

	redir_lst = NULL;
	while (token_lst && token_lst->token != OPERATOR)
	{
		if (token_lst->token == PARENTHESIS)
			token_lst = skip_forward_parenthesis(token_lst);
		else if (token_lst->token == IN_FILE_TRUNC || token_lst->token == OUT_FILE_TRUNC || token_lst->token == HERE_DOC || token_lst->token == OUT_FILE_APPEND)
			tok_add_back(&redir_lst, copy_tok(token_lst));
		token_lst = token_lst->next;
	}
	return (redir_lst);
}

t_parenthesis	*parenthesis_node(t_token *token_lst)
{
	t_parenthesis	*parenthesis_node;
	t_token			*new_token_lst;

	parenthesis_node = (t_parenthesis *)malloc(sizeof(t_parenthesis));
	parenthesis_node->redir_list = parenthesis_redirections(token_lst);
	new_token_lst = skip_par_tokens(token_lst);
	initializePrevious(new_token_lst);
	if (new_token_lst)
			while (new_token_lst->next)
				new_token_lst = new_token_lst->next;
	parenthesis_node->tree = tree_create(new_token_lst, OP);
	return (parenthesis_node);
}
