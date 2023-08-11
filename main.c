/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/11 17:11:49 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *str;
	// char **splitcmd;
	char *res_fix_syntax;

	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		res_fix_syntax = fix_syntax(str);
		check_parentheses(res_fix_syntax);
		check_quotes(res_fix_syntax);
		printf("%s\n", res_fix_syntax);
		// splitcmd = ft_split(res_fix_syntax, ' ');
		// free(res_fix_syntax);
		// for (int i = 0; splitcmd[i]; i++)
		// 	printf("%s ", splitcmd[i]);
		// printf("\n");
		// tokenizer(splitcmd);
		// free_matrix(splitcmd);
		free(str);
	}
}
