/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/08 12:02:13 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *str;
	char **splitcmd;
	char *res_fix_syntax;

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
		tokenizer(splitcmd);
		free_matrix(splitcmd);
		free(str);
	}
}
