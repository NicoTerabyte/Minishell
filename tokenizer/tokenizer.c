/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:38 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/18 14:36:28 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	initializePrevious(t_token *head)
{
	t_token* current = head;
	t_token* prevNode = NULL;

	while (current != NULL)
	{
		current->prev = prevNode;
		prevNode = current;
		current = current->next;
	}
}

void	print_tokens(t_token *token_lst)
{
	t_declaration	*type_decl;
	char			*type_char;
	char			**args;
	// t_token			*tmp;
	// t_declaration	*tmpdecl;
	int				i;

	i = 0;
	while (token_lst)
	{
		if (token_lst->token == PARENTHESIS || token_lst->token == IN_FILE_TRUNC
				|| token_lst->token == HERE_DOC || token_lst->token == OUT_FILE_APPEND
				|| token_lst->token == OUT_FILE_TRUNC || token_lst->token == CMD_NAME
				|| token_lst->token == OPERATOR)
		{
			type_char = (char *)token_lst->value;
			printf("tipo : %d, contenuto : %s\n", token_lst->token, type_char);
			// if (token_lst->token == OPERATOR || token_lst->token == OUT_FILE_APPEND || token_lst->token == OUT_FILE_TRUNC || token_lst->token == HERE_DOC
			// 		|| token_lst->token == IN_FILE_TRUNC || token_lst->token == OPERATOR || token_lst->token == CMD_NAME)
				// free(type_char);
		}
		else if (token_lst->token == ENV_VAR_DECL || token_lst->token == ENV_VAR_UNSET)
		{
			type_decl = (t_declaration *)token_lst->value;
			printf("tipo : %d, contenuto : ", token_lst->token);
			while (type_decl)
			{
				printf("(var name : %s, var value : %s, conc mode : %d) ", type_decl->name, type_decl->value, type_decl->concatenation);
				// tmpdecl = type_decl;
				type_decl = type_decl->next;
				// free(tmpdecl->name);
				// if (tmpdecl->value)
					// free(tmpdecl->value);
				// free(tmpdecl);
			}
			printf("\n");
		}
		else if (token_lst->token == CMD_ARG)
		{
			i = 0;
			args = (char **)token_lst->value;
			printf("tipo : %d, contenuto : (", token_lst->token);
			while(args[i])
			{
				printf(" %s", args[i]);
				// free(args[i]);
				i++;
			}
			// free(args);
			printf(" )\n");
		}
		// tmp = token_lst;
		token_lst = token_lst->next;
		// free(tmp);
	}
	// free(token_lst);
}

t_token	*tokenizer(char **splitcmd)
{
	t_token *token_lst;
	int	i;
	int	cursor;

	i = 0;
	cursor = 0;
	token_lst = NULL;
	while (splitcmd[i])
	{
		cursor = i;
		scan_parenthesis(splitcmd, &i, &token_lst);
		scan_redirections(splitcmd, &i, &token_lst);
		if (verify_env_decl(splitcmd, &i))
			scan_env_decl(splitcmd, &i, &token_lst);
		else
			scan_cmd(splitcmd, &i, &token_lst);
		scan_redirections(splitcmd, &i, &token_lst);
		scan_parenthesis(splitcmd, &i, &token_lst);
		scan_redirections(splitcmd, &i, &token_lst);
		scan_operator(splitcmd, &i, &token_lst);
		if (cursor == i)
			break ;
	}
	initializePrevious(token_lst);
	// print_tokens(token_lst);
	if (token_lst == NULL)
		printf("merda\n");
	return (token_lst);
}
