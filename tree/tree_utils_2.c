/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:00:14 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/10 13:07:34 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tree_init_norm(t_tree *tree)
{
	tree->content = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->prev = NULL;
}

t_token	*skip_back_parenthesis(t_token *token_lst)
{
	int		n_parenthesis;
	char	*value;

	n_parenthesis = 1;
	while (token_lst->prev && n_parenthesis)
	{
		token_lst = token_lst->prev;
		if (token_lst->token == PARENTHESIS)
		{
			value = (char *)token_lst->value;
			if (ft_strncmp(value, ")", 1) == 0)
				n_parenthesis++;
			else
				n_parenthesis--;
		}
	}
	if (token_lst->prev != NULL)
		return (token_lst->prev);
	else
		return (token_lst);
}