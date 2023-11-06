/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:18:00 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/06 17:18:09 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_number_back(char *s, char *start)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (&s[i] != start)
	{
		if (s[i] == '"')
		{
			i--;
			while (s[i] != '"' && &s[i] != start)
				i--;
		}
		if (s[i] == '\'')
		{
			i--;
			while (s[i] != '\'' && &s[i] != start)
				i--;
		}
		if (s[i] == '(')
			count--;
		if (s[i] == ')')
			count++;
		i--;
	}
	if (s[i] == '(')
		count--;
	if (s[i] == ')')
		count++;
	if (count != 0)
		return (0);
	return (1);
}

int check_number(char *s)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"' && s[i] != '\0')
				i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
		}
		if (s[i] == '(')
			count++;
		if (s[i] == ')')
			count--;
		i++;
	}
	if (count != 0)
		return (0);
	return (1);
}
