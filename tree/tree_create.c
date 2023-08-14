#include "tree.h"

// void	tree_node_operator(t_token **token_lst, t_tree **tree)
// {
// 	t_tree
// 	if ((*tree)->prev == NULL)
// 		(*tree)->type = OP;
// 	else
// 	{

// 	}
// }


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
		//da verificare il caso in cui ci possa essere una parentesi
		if (token_lst->token == IN_FILE_TRUNC || token_lst->token == OUT_FILE_TRUNC || token_lst->token == HERE_DOC || token_lst->token == OUT_FILE_APPEND)
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
		printf("%d\n", token_lst->token);
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

//prima di entrare bisogna fare l'inizializeprevious function e andare alla fine di token_lst
t_tree *tree_create(t_token **token_lst, t_tree_enum calling)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->content = NULL;
	tree->left = NULL;
	tree->right = NULL;
	tree->prev = NULL;
	if (calling == SIMPLE_CMD)
	{
		tree->type = SIMPLE_CMD;
		tree->content = simple_cmd_redirections((*token_lst));
		simple_cmd((*token_lst), tree->content);
		return (tree);
	}
	// else if (calling == OP)
	// {
	// 	while ((*token_lst)->prev != NULL)
	// 	{
	// 		if ((*token_lst)->token == OPERATOR)
	// 			tree_node_operator(token_lst, &tree);
	// 		(*token_lst) = (*token_lst)->prev;
	// 	}
	// }
	// if (calling == OP)
	// 	return (tree_create(token_lst, SIMPLE_CMD));
	return (tree);
}
