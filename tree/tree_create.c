#include "tree.h"

t_token	*skip_forward_parenthesis(t_token *token_lst)
{
	int		n_parenthesis;
	char	*value;

	n_parenthesis = 1;
	while (token_lst->next && n_parenthesis)
	{
		token_lst = token_lst->next;
		if (token_lst->token == PARENTHESIS)
		{
			value = (char *)token_lst->value;
			if (ft_strncmp(value, "(", 1) == 0)
				n_parenthesis++;
			else
				n_parenthesis--;
		}
	}
	return (token_lst);
}

void	tree_node_operator(t_token *token_lst, t_tree **tree)
{
	(*tree)->type = OP;
	(*tree)->content = token_lst->value;
	token_lst = token_lst->prev;
	(*tree)->left = tree_create(token_lst, OP);
	token_lst = token_lst->next;
	token_lst = token_lst->next;
	(*tree)->right = tree_create(token_lst, SIMPLE_CMD);
}

t_token	*copy_tok(t_token *to_copy)
{
	t_token	*res;

	res = (t_token *)malloc(sizeof(t_token));
	res->next = NULL;
	res->token = to_copy->token;
	res->value = to_copy->value;
	res->prev = NULL;
	return(res);
}

t_simple_cmd	*simple_cmd_redirections(t_token *token_lst)
{
	t_simple_cmd *simple_cmd;

	simple_cmd = (t_simple_cmd *)malloc(sizeof(t_simple_cmd));
	simple_cmd->redir_list = NULL;
	simple_cmd->cmd = NULL;
	simple_cmd->env = NULL;
	while (token_lst && token_lst->token != OPERATOR)
	{
		if (token_lst->token == PARENTHESIS)
			token_lst = skip_forward_parenthesis(token_lst);
		else if (token_lst->token == IN_FILE_TRUNC || token_lst->token == OUT_FILE_TRUNC || token_lst->token == HERE_DOC || token_lst->token == OUT_FILE_APPEND)
			tok_add_back(&simple_cmd->redir_list, copy_tok(token_lst));
		token_lst = token_lst->next;
	}
	return (simple_cmd);
}

void	simple_cmd(t_token *token_lst, t_simple_cmd *simple_cmd)
{
	simple_cmd->cmd = (t_cmd *)malloc(sizeof(t_cmd));
	simple_cmd->cmd->cmd_arg = NULL;
	simple_cmd->cmd->cmd_name = NULL;
	while (token_lst && token_lst->token != OPERATOR)
	{
		//da verificare il caso in cui ci possa essere una parentesi
		if (token_lst->token == CMD_ARG)
		{
			tok_add_back(&simple_cmd->cmd->cmd_arg, copy_tok(token_lst));
			tok_add_back(&simple_cmd->cmd->cmd_name, copy_tok(token_lst->next));
			return ;
		}
		else if (token_lst->token == CMD_NAME)
		{
			tok_add_back(&simple_cmd->cmd->cmd_name, copy_tok(token_lst));
			return ;
		}
		else if (token_lst->token == ENV_VAR_DECL || token_lst->token == ENV_VAR_UNSET)
		{
			tok_add_back(&simple_cmd->env, copy_tok(token_lst));
			return ;
		}
		else
			token_lst = token_lst->next;
	}
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

int	verify_parenthesis(t_token *token_lst)
{
	while (token_lst->next && token_lst->token != OPERATOR)
	{
		if (token_lst->token == PARENTHESIS)
			return (1);
		token_lst = token_lst->next;
	}
	return (0);
}

t_token	*skip_par_tokens(t_token *token_lst)
{
	t_token	*new_token_lst;
	int		n_parenthesis;
	char	*value;

	n_parenthesis = 1;
	new_token_lst = NULL;
	token_lst = token_lst->next;
	while (token_lst && n_parenthesis)
	{
		if (token_lst->token == PARENTHESIS)
		{
			value = (char *)token_lst->value;
			if (ft_strncmp(value, "(", 1) == 0)
				n_parenthesis++;
			else
				n_parenthesis--;
		}
		if (n_parenthesis)
		{
			tok_add_back(&new_token_lst, copy_tok(token_lst));
			token_lst = token_lst->next;
		}
	}
	// printf("PRINT TOKENS PARENTHESIS\n");
	// print_tokens(new_token_lst);
	return (new_token_lst);
}

t_token	*parenthesis_redirections(t_token *token_lst)
{
	t_token	*redir_lst;

	redir_lst = NULL;
	while (token_lst && token_lst->token != OPERATOR)
	{
		if (token_lst->token == PARENTHESIS)
			token_lst = skip_forward_parenthesis(token_lst);
		else if (token_lst->token == IN_FILE_TRUNC || token_lst->token == OUT_FILE_TRUNC || token_lst->token == HERE_DOC || token_lst->token == OUT_FILE_APPEND)
			tok_add_back(&redir_lst, copy_tok(token_lst));
		token_lst = token_lst->next;
	}
	return (redir_lst);
}

t_parenthesis	*parenthesis_node(t_token *token_lst)
{
	t_parenthesis	*parenthesis_node;
	t_token			*new_token_lst;

	parenthesis_node = (t_parenthesis *)malloc(sizeof(t_parenthesis));
	parenthesis_node->redir_list = parenthesis_redirections(token_lst);
	new_token_lst = skip_par_tokens(token_lst);
	initializePrevious(new_token_lst);
	if (new_token_lst)
			while (new_token_lst->next)
				new_token_lst = new_token_lst->next;
	parenthesis_node->tree = tree_create(new_token_lst, OP);
	return (parenthesis_node);
}

t_tree *tree_create(t_token *token_lst, t_tree_enum calling)
{
	if (!token_lst)
		return (NULL);
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->content = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->prev = NULL;
	if (calling == SIMPLE_CMD)
	{
		if (verify_parenthesis(token_lst))
		{
			tree->type = PARENTHESI;
			tree->content = parenthesis_node(token_lst);
			return (tree);
		}
		tree->type = SIMPLE_CMD;
		tree->content = simple_cmd_redirections((token_lst));
		simple_cmd(token_lst, tree->content);
		return (tree);
	}
	else if (calling == OP)
	{
		while (token_lst->prev != NULL)
		{
			if (token_lst->token == OPERATOR)
			{
				tree_node_operator(token_lst, &tree);
				return (tree);
			}
			else if (token_lst->token == PARENTHESIS)
				token_lst = skip_back_parenthesis(token_lst);
			else
				token_lst = token_lst->prev;
		}
	}
	return (tree_create(token_lst, SIMPLE_CMD));
}
