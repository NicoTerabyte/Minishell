/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/07 19:08:00 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *str;
	char **splitcmd;
	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		//qui va fatto prima un lexer
		splitcmd = ft_split(fix_syntax(str), ' ');
		for (int i = 0; splitcmd[i]; i++)
			printf("%s ", splitcmd[i]);
		printf("\n");
		tokenizer(splitcmd);
		free_matrix(splitcmd);
		free(str);
	}
}
