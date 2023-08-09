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

void	scan_redirections(char **splitcmd, int *i, t_token *token_lst)
{
	t_token	*token;

	if (!splitcmd[*i])
		return ;
	if (!((splitcmd[*i][0] == '>' && splitcmd[*i][1] == '>') || (splitcmd[*i][0] == '<' && splitcmd[*i][1] == '<') || splitcmd[*i][0] == '>' || splitcmd[*i][0] == '<'))
		return ;
	token = (t_token *)malloc(sizeof(t_token));
	token->token = set_redir_type();


}
