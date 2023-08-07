#include "minishell.h"

void scan_parenthesis(char **splitwords, int *i, t_token **token_lst)
{
	t_token *tok_par;

	if (!splitwords[*i])
		return ;
	while (splitwords[*i][0] == '(' || splitwords[*i][0] == ')')
	{
		tok_par = (t_token *)malloc(sizeof(t_token));
		if (splitwords[*i][0] == '(')
		{
			tok_par->token = PARENTHESIS;
			tok_par->value = (int *)i;
			tok_par->next = NULL;
			*i += 1;
			tok_add_back(token_lst, tok_par);
		}
		else if (splitwords[*i][0] == ')')
		{
			tok_par->token = PARENTHESIS;
			tok_par->value = (int *)i;
			tok_par->next = NULL;
			*i += 1;
			tok_add_back(token_lst, tok_par);
		}
		else
			free(tok_par);
	}
}

// void scan_redirections(char **splitwords, int *i, t_token *token_lst)
// {

// }
