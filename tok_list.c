#include "minishell.h"

void	tok_add_back(t_token **lst, t_token *new)
{
	static t_token	*tail = NULL;

	if (!(*lst))
	{
		*lst = new;
		tail = *lst;
	}
	else
	{
		tail->next = new;
		tail = tail->next;
	}
	tail->next = NULL;
}
