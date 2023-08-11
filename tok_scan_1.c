/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_scan_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:24 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/11 12:48:05 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	scan_parenthesis(char **splitcmd, int *i, t_token **token_lst)
{
	t_token *tok_par;

	if (!splitcmd[*i])
		return ;
	while (splitcmd[*i] && (splitcmd[*i][0] == '(' || splitcmd[*i][0] == ')'))
	{
		tok_par = (t_token *)malloc(sizeof(t_token));
		if (splitcmd[*i][0] == '(')
		{
			tok_par->token = PARENTHESIS;
			tok_par->value = "(";
			tok_par->next = NULL;
			*i += 1;
			tok_add_back(token_lst, tok_par);
		}
		else if (splitcmd[*i][0] == ')')
		{
			tok_par->token = PARENTHESIS;
			tok_par->value = ")";
			tok_par->next = NULL;
			*i += 1;
			tok_add_back(token_lst, tok_par);
		}
		else
			free(tok_par);
	}
}

void	scan_operator(char **splitcmd, int *i, t_token **token_lst)
{
	t_token	*token_op;

	if (!splitcmd[*i] || !((splitcmd[*i][0] == '|' && splitcmd[*i][1] == '|') || (splitcmd[*i][0] == '&' && splitcmd[*i][1] == '&') || splitcmd[*i][0] == '|'))
		return ;
	token_op = (t_token *)malloc(sizeof(t_token));
	token_op->token = OPERATOR;
	token_op->value = ft_substr(splitcmd[*i], 0, ft_strlen(splitcmd[*i]));
	token_op->next = NULL;
	tok_add_back(token_lst, token_op);
	*i += 1;
}
