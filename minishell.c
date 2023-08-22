/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/22 13:36:54 by mlongo           ###   ########.fr       */
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
		free_matrix(splitcmd);
		free(str);
	}
}
