/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/22 16:30:40 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	last_exit_status_cmd = 0;

void printTree(t_tree *node, int level, char *message) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
	printf("%s\n", message);
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    if (node->type == SIMPLE_CMD) {
        t_simple_cmd *cmd = (t_simple_cmd *)node->content;
        printf("SIMPLE_CMD\n");
		print_tokens(cmd->redir_list);
		for (int i = 0; i < level; i++) {
  	    	printf("  ");
   		}
        print_tokens(cmd->cmd->cmd_arg);
		for (int i = 0; i < level; i++) {
  	    	printf("  ");
   		}
        print_tokens(cmd->cmd->cmd_name);
        print_tokens(cmd->env);
    } else if (node->type == OP) {
        printf("OP\n");
        char *cmd = (char *)node->content;
		printf("content : %s\n", cmd);
    } else if (node->type == PARENTHESI) {
        printf("PARENTHESIS\n");
        t_parenthesis *cmd = (t_parenthesis *)node->content;
		print_tokens(cmd->redir_list);
		printTree(cmd->tree, level, "ROOT PARENTHESIS");
    }

    printTree(node->left, level + 1, "LEFT");
    printTree(node->right, level + 1, "RIGHT");
}

char	**env_container(int action, void *arg)
{
	static char **env;

	if (action == 0)
		env = (char **)arg;
	return (env);
}

void	free_tokens(t_token *token_lst)
{
	t_token			*tmp;
	t_declaration	*type_decl;
	t_declaration	*tmpdecl;
	char			**args;
	int				i;

	i = 0;
	while (token_lst)
	{
		if (token_lst->token == PARENTHESIS || token_lst->token == IN_FILE_TRUNC
				|| token_lst->token == HERE_DOC || token_lst->token == OUT_FILE_APPEND
				|| token_lst->token == OUT_FILE_TRUNC || token_lst->token == CMD_NAME
				|| token_lst->token == OPERATOR)
		{
			if (token_lst->token == OPERATOR || token_lst->token == OUT_FILE_APPEND || token_lst->token == OUT_FILE_TRUNC || token_lst->token == HERE_DOC
					|| token_lst->token == IN_FILE_TRUNC || token_lst->token == OPERATOR || token_lst->token == CMD_NAME)
				free(token_lst->value);
		}
		else if (token_lst->token == ENV_VAR_DECL || token_lst->token == ENV_VAR_UNSET)
		{
			type_decl = (t_declaration *)token_lst->value;
			while (type_decl)
			{
				tmpdecl = type_decl;
				type_decl = type_decl->next;
				free(tmpdecl->name);
				if (tmpdecl->value)
					free(tmpdecl->value);
				free(tmpdecl);
			}
		}
		else if (token_lst->token == CMD_ARG)
		{
			i = 0;
			args = (char **)token_lst->value;
			while(args[i])
			{
				free(args[i]);
				i++;
			}
			free(args);
		}
		tmp = token_lst;
		token_lst = token_lst->next;
		free(tmp);
	}
	free(token_lst);
}

void	free_tree(t_tree *tree)
{
	t_parenthesis	*par;
	t_simple_cmd	*cmd;

	if (!tree)
		return ;

	if (tree->type == PARENTHESI)
	{
		par = (t_parenthesis *)tree->content;
		free_tokens((t_token *)par->redir_list);
		free_tree((t_tree *)par->tree);
	}
	else if (tree->type == SIMPLE_CMD)
	{
		cmd = (t_simple_cmd *)tree->content;
		free_tokens(cmd->redir_list);
		free_tokens(cmd->cmd->cmd_arg);
		free_tokens(cmd->cmd->cmd_name);
		free_tokens(cmd->env);
	}
	free_tree(tree->left);
	free_tree(tree->right);
	free(tree);
}

void	ft_free_all(t_token *token_lst, t_tree *tree)
{
	free_tokens(token_lst);
	free_tree(tree);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	char	*str;
	char	**splitcmd;
	char	*res_fix_syntax;
	t_token	*token_list;
	t_tree	*tree;

	env_container(0, envp);

	token_list = NULL;
	while (1)
	{
		str = readline("minishell> ");
		// str = "cat global./h && cat minishell.h";
		add_history(str);
		//qui va fatto prima un lexer
		res_fix_syntax = fix_syntax(str);
		// printf("%s\n", res_fix_syntax);
		splitcmd = ft_split(res_fix_syntax, ' ');
		// free(res_fix_syntax);
		// for (int i = 0; splitcmd[i]; i++)
		// 	printf("%s ", splitcmd[i]);
		// printf("\n");
		token_list = tokenizer(splitcmd);
		// print_tokens(token_list);
		if (token_list)
			while (token_list->next)
				token_list = token_list->next;
		tree = tree_create(token_list, OP);
		// printTree(tree, 0, "ROOT");
		execute(tree, STDIN_FILENO, STDOUT_FILENO);
		printf("%d\n", last_exit_status_cmd);
		free_matrix(splitcmd);
		ft_free_all(token_list, tree);
		free(str);
	}
}
