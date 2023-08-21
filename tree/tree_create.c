/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 11:51:13 by alessiolong       #+#    #+#             */
/*   Updated: 2023/08/20 11:51:14 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tree.h"


void	tree_node_operator(t_token *token_lst, t_tree **tree)
{
	(*tree)->type = OP;
	(*tree)->content = token_lst->value;
	token_lst = token_lst->prev;
	(*tree)->left = tree_create(token_lst, OP);
	token_lst = token_lst->next;
	token_lst = token_lst->next;
	(*tree)->right = tree_create(token_lst, SIMPLE_CMD);
}

t_tree *tree_create(t_token *token_lst, t_tree_enum calling)
{
	if (!token_lst)
		return (NULL);
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->content = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->prev = NULL;
	if (calling == SIMPLE_CMD)
	{
		if (verify_parenthesis(token_lst))
		{
			tree->type = PARENTHESI;
			tree->content = parenthesis_node(token_lst);
			return (tree);
		}
		tree->type = SIMPLE_CMD;
		tree->content = simple_cmd_redirections((token_lst));
		simple_cmd(token_lst, tree->content);
		return (tree);
	}
	else if (calling == OP)
	{
		while (token_lst->prev != NULL)
		{
			if (token_lst->token == OPERATOR)
			{
				tree_node_operator(token_lst, &tree);
				return (tree);
			}
			else if (token_lst->token == PARENTHESIS)
				token_lst = skip_back_parenthesis(token_lst);
			else
				token_lst = token_lst->prev;
		}
	}
	return (tree_create(token_lst, SIMPLE_CMD));
}
