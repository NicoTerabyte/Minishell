/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/17 18:26:25 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
    } else if (node->type == PARENTHESIS) {
        printf("PARENTHESIS\n");
        t_parenthesis *cmd = (t_parenthesis *)node->content;
		print_tokens(cmd->redir_list);
		printTree(cmd->tree, level, "ROOT PARENTHESIS");
    }

    printTree(node->left, level + 1, "LEFT");
    printTree(node->right, level + 1, "RIGHT");
}

int main()
{
	char	*str;
	char	**splitcmd;
	char	*res_fix_syntax;
	t_token	*token_list;
	t_tree	*tree;

	token_list = NULL;
	while (1)
	{
		str = readline("minishell> ");
		// str = "cat ciao | (ok)";
		add_history(str);
		//qui va fatto prima un lexer
		res_fix_syntax = fix_syntax(str);
		splitcmd = ft_split(res_fix_syntax, ' ');
		free(res_fix_syntax);
		for (int i = 0; splitcmd[i]; i++)
			printf("%s ", splitcmd[i]);
		printf("\n");
		token_list = tokenizer(splitcmd);
		if (token_list)
			while (token_list->next)
				token_list = token_list->next;
		tree = tree_create(&token_list, OP);
		printTree(tree, 0, "ROOT");
		free_matrix(splitcmd);
		free(str);
	}
}
