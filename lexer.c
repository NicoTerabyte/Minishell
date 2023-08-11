/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:08:48 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/11 17:13:53 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void check_parentheses(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '(')
		{
			if ((str[i - 2] != '&' || str[i - 3] != '&') && i != 0)
			{
				printf("syntax error near unexpected token '('\n");
				return ;
			}
			count++;
		}
		if (str[i] == ')')
			count--;
		i++;
	}
	if (count != 0)
		printf("Syntax error : Missing parentheses\n");
}

void check_quotes(char *str)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
			count++;
		i++;
	}
	if (count % 2 != 0)
		printf("Syntax error : Missing quotes\n");
}
