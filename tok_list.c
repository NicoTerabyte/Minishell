#include "minishell.h"

void	tok_add_back(t_token **lst, t_token *new)
{
	if (!lst)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while ((*lst)->next)
		(*lst) = (*lst)->next;
	(*lst)->next = new;
}
