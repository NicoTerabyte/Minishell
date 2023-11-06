/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:14:29 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/06 18:34:13 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_parentheses(char *s, int *i)
{
	if (*i != 0)
	{
		if (s[*i - 2] == '(' && check_number(s))
			return (1);
		if (!((s[*i - 2] == '&' && s[*i - 3] == '&') || (s[*i - 2] == '|' && s[*i - 3] == '|') || (s[*i - 2] == '|' && s[*i - 3] == ' ')))
			return (0);
	}
	if (check_number(s))
		return (1);
	return (0);
}

int check_back(char *s, int i)
{
	if (s[i - 2] == ')')
	{
		while (i >= 0)
		{
			if (s[i - 2] == '(')
				return (1);
			i--;
		}
		return (0);
	}
	return (1);
}

int check_quote(char *s)
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
			count++;
			while (s[i] != '"' && s[i] != '\0')
				i++;
			if (s[i] == '"')
			count--;
		}
		if (s[i] == '\'')
		{
			i++;
			count++;
			while (s[i] != '\'' && s[i] != '\0')
				i++;
			if (s[i] == '\'')
			count--;
		}
		i++;
	}
	if (count != 0)
		return (0);
	return (1);
}

int check_operator(char *s, int *i)
{
	if (s[*i] == '>' || s[*i] == '<')
	{
		if ((s[*i] == s[*i + 1] && s[*i + 2] == ' ' && s[*i + 3] != '>' && s[*i + 4] != '<') || (s[*i + 1] == ' ' && s[*i + 2] != '>' && s[*i + 3] != '<'))
			return (1);
	}
	if (s[*i + 1] == 0 || s[*i + 2] == 0 || *i == 0)
		return (0);
	if (is_double(s, i))
		return (0);
	if ((not_op(&s[*i - 3]) || not_op(&s[*i - 2])) && s[*i - 1] == ' ')
	{
		if (s[*i] == s[*i + 1] && s[*i + 2] == ' ' && not_op(&s[*i + 3]))
		{
			(*i)++;
			return (1);
		}
		if (s[*i] == '|' && s[*i + 1] == ' ' && not_op(&s[*i + 2]))
			return (1);
	}
	return (0);
}
