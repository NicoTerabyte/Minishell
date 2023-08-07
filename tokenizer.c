#include "minishell.h"

void	print_tokens(t_token *token_lst)
{
	int *type;

	type = NULL;
	while (token_lst)
	{
		printf("ok");
		type = (int *)token_lst->value;
		printf("tipo : %d, contenuto : %d\n", token_lst->token, *type);
		token_lst = token_lst->next;
	}
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
		// printf("ok");
		scan_parenthesis(splitcmd, &i, &token_lst);
		// printf("ok");
		// scan_redirections(splitcmd, &i, token_lst);
		// if (verify_env_decl(splitcmd, &i))
		// 	scan_env_decl(splitcmd, &i, token_lst);
		// else
		// 	scan_cmd(splitcmd, &i, token_lst);
		// scan_redirections(splitcmd, &i, token_lst);
		// scan_parenthesis(splitcmd, &i, token_lst);
		// scan_redirections(splitcmd, &i, token_lst);
		// scan_operator(splitcmd, &i, token_lst);
		if (cursor == i)
			break ;
	}
	print_tokens(token_lst);
	return (token_lst);
}
