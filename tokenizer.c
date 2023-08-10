#include "minishell.h"

void	print_tokens(t_token *token_lst)
{
	t_declaration	*type_decl;
	char			*type_parenthesis;
	t_token			*tmp;
	t_declaration	*tmpdecl;

	while (token_lst)
	{
		if (token_lst->token == PARENTHESIS)
		{
			type_parenthesis = (char *)token_lst->value;
			printf("tipo : %d, contenuto : %s\n", token_lst->token, type_parenthesis);
		}
		else if (token_lst->token == ENV_VAR_DECL || token_lst->token == ENV_VAR_UNSET)
		{
			type_decl = (t_declaration *)token_lst->value;
			printf("tipo : %d, contenuto : \n", token_lst->token);
			while (type_decl)
			{
				printf("var name : %s, var value : %s, conc mode : %d\n", type_decl->name, type_decl->value, type_decl->concatenation);
				tmpdecl = type_decl;
				type_decl = type_decl->next;
				free(tmpdecl->name);
				if (tmpdecl->value)
					free(tmpdecl->value);
				free(tmpdecl);
			}
		}
		tmp = token_lst;
		token_lst = token_lst->next;
		free(tmp);
	}
	free(token_lst);
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
		// scan_parenthesis(splitcmd, &i, &token_lst);
		scan_redirections(splitcmd, &i, &token_lst);
		// if (verify_env_decl(splitcmd, &i))
		// 	scan_env_decl(splitcmd, &i, &token_lst);
		// else
		// 	printf("not env\n");
			// scan_cmd(splitcmd, &i, token_lst);
		// scan_redirections(splitcmd, &i, token_lst);
		// scan_parenthesis(splitcmd, &i, token_lst);
		// scan_redirections(splitcmd, &i, token_lst);
		// scan_operator(splitcmd, &i, token_lst);
		if (cursor == i)
			break ;
	}
	// print_tokens(token_lst);
	return (token_lst);
}
