#include "minishell.h"

t_token_enum set_redir_type(char **splitcmd, int *i)
{
	t_token_enum enum_tok;

	enum_tok = NONE;
	if (!splitcmd[*i])
		return (enum_tok);
	if (splitcmd[*i][0] == '>' && splitcmd[*i][1] == '>')
		return (OUT_FILE_APPEND);
	else if (splitcmd[*i][0] == '<' && splitcmd[*i][1] == '<')
		return (HERE_DOC);
	else if (splitcmd[*i][0] == '>')
		return (OUT_FILE_TRUNC);
	else if (splitcmd[*i][0] == '<')
		return (IN_FILE_TRUNC);
	*i += 1;
	return (enum_tok);
}

char	*set_redir_type(char **splitcmd, int *i)
{
	//espansione e no quotes splitcmd[*i]
	return (ft_substr(splitcmd[*i], 0, ft_strlen(splitcmd[*i])));
}
void	scan_redirections(char **splitcmd, int *i, t_token *token_lst)
{
	t_token	*token;

	if (!splitcmd[*i])
		return ;
	if (!((splitcmd[*i][0] == '>' && splitcmd[*i][1] == '>') || (splitcmd[*i][0] == '<' && splitcmd[*i][1] == '<') || splitcmd[*i][0] == '>' || splitcmd[*i][0] == '<'))
		return ;
	token = (t_token *)malloc(sizeof(t_token));
	token->token = set_redir_type(splitcmd, i);
	if (token->token == NONE)
		return ;
	if (token->token == HERE_DOC)
		return ;
	else
		token->value = set_redir_value(splitcmd, i);
}
