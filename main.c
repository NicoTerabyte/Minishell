/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/14 18:49:54 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void printTree(t_tree *node, int level) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    if (node->type == SIMPLE_CMD) {
        t_simple_cmd *cmd = (t_simple_cmd *)node->content;
        printf("SIMPLE_CMD\n");
		print_tokens(cmd->redir_list);
        print_tokens(cmd->cmd->cmd_arg);
        print_tokens(cmd->cmd->cmd_name);
    } else if (node->type == OP) {
        printf("OP\n");
    } else if (node->type == PARENTHESIS) {
        printf("PARENTHESIS\n");
    }

    printTree(node->left, level + 1);
    printTree(node->right, level + 1);
}

int main()
{
	char	*str;
	char	**splitcmd;
	char	*res_fix_syntax;
	t_token	*token_list;
	t_tree	*tree;

	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		//qui va fatto prima un lexer
		res_fix_syntax = fix_syntax(str);
		splitcmd = ft_split(res_fix_syntax, ' ');
		free(res_fix_syntax);
		for (int i = 0; splitcmd[i]; i++)
			printf("%s ", splitcmd[i]);
		printf("\n");
		token_list = tokenizer(splitcmd);
		tree = tree_create(&token_list, SIMPLE_CMD);
		printTree(tree, 0);
		free_matrix(splitcmd);
		free(str);
	}
}
