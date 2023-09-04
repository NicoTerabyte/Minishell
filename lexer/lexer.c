/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fla <fla@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 15:08:48 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/09/02 16:03:43 by fla              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "lexer.h"

// int check_parentheses(char *str)
// {
// 	int	i;
// 	int count;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '(')
// 		{
// 			if (check_back(str, i, 1) == -1)
// 			{
// 				printf("Syntax error : Missing parentheses\n");
// 				return (-1);
// 			}
// 			count++;
// 		}
// 		if (str[i] == ')')
// 			count--;
// 		i++;
// 	}
// 	if (count != 0)
// 	{
// 		printf("Syntax error : Missing parentheses\n");
// 		return (-1);
// 	}
// 	return (1);
// }

// int	check_quotes(char *str)
// {
// 	int	i;
// 	int count;
// 	char quote;

// 	i = 0;
// 	count = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\'' || str[i] == '"')
// 		{
// 			count++;
// 			quote = str[i];
// 			while (str[i] != quote)
// 				i++;
// 			if (str[i] != quote)  // && !ft_isspace(str[i + 1])
// 			{
// 				printf("Syntax error : Missing quotes\n");
// 				return (-1);
// 			}
// 			count++;
// 		}
// 		i++;
// 	}
// 	if (count % 2 != 0)
// 	{
// 		printf("Syntax error : Missing quotes\n");
// 		return (-1);
// 	}
// 	return (1);
// }

// static int	ft_isalpha(char c)
// {
// 	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
// 		return (1);
// 	return (0);
// }

// int check_back(char *s, int i, int n)
// {
// 	if (n == 0)
// 	{
// 		while (!ft_isalpha(s[i]))
// 			i--;
// 		if (s[i] >= 65 && s[i] <= 122)
// 			return (1);
// 	}
// 	if (n == 1 && i != 0)
// 	{
// 		if ((s[i - 2] == '&' && s[i - 3] == '&') ||  (s[i - 2] == '|' && s[i - 3] == '|') || (s[i - 2] == '|' && s[i - 3] == ' ') || (s[i - 1] == '$' && s[i - 2] == '='))
// 			return (1);
// 	}
// 	return (-1);
// }

// int	check_operators(char *str)
// {
// 	int i;
	
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (check_back(str, i, 1))
// 		{
// 			if (!check_back(str, i, 0))
// 			{
// 				printf("Syntax error : Wrong operation\n");
// 				return (-1);
// 			}
// 		}
// 		i++;
// 	}
// 	return (1);
// }

// int	check_content(char *str, int i)
// {
// 	char	quote;

// 	quote = str[i];
// 	while (str[i++])
// 	{
// 		if (str[i] == quote)
// 			break ;
// 		else if (str[i] == 0)
// 			return (-1);
// 	}
// 	if (!ft_isspace(str[i + 1]) && str[i + 1] != '&' && str[i + 1] != '|' && str[i + 1] != 0)
// 		return (-1);
// 	return (i);
// }

// char	*back_str(char *str, int i)
// {
// 	char	*s;
// 	char	quote;
// 	int		j;
	
// 	s = malloc(100);
// 	if (!s)
// 	{
// 		printf("Errore: impossibile allocare memoria.\n");
//         exit(1);
// 	}
// 	j = 0;
// 	while (str[i] != ' ')
// 	{
// 		if (str[i] == ')')
// 		{
// 			while (str[i] != '(')
// 				s[j++] = str[i--];
// 			while (j < 100)
// 				s[j++] = 0;
// 			return (s);
// 		}
// 		if (str[i] == '"' || str[i] == '\'')
// 		{
// 			quote = str[i];
// 			while (str[i] != quote)
// 				s[j++] = str[i--];
// 			while (j < 100)
// 				s[j++] = 0;
// 			return (s);
// 		}
// 		s[j++] = str[i--];
// 	}
// 	while (j < 100)
// 		s[j++] = 0;
// 	return(s);
// }

// char	*next_str(char *str, int i)
// {
// 	char	*s;
// 	char	quote;
// 	int		j;
	
// 	s = malloc(100);
// 	if (!s)
// 	{
// 		printf("Errore: impossibile allocare memoria.\n");
//         exit(1);
// 	}
// 	j = 0;
// 	i += 2;
// 	while (str[i] != ' ')
// 	{
// 		if (str[i] == '(')
// 		{
// 			while (str[i] != ')')
// 				s[j++] = str[i++];
// 			while (j < 100)
// 				s[j++] = 0;
// 			return (s);
// 		}
// 		if (str[i] == '"' || str[i] == '\'')
// 		{
// 			quote = str[i];
// 			while (str[i] != quote)
// 				s[j++] = str[i++];
// 			while (j < 100)
// 				s[j++] = 0;
// 			return (s);
// 		}
// 		s[j++] = str[i++];
// 	}
// 	while (j < 100)
// 		s[j++] = 0;
// 	return(s);
// }

// int	check_operators(char *str, int i)
// {
// 	char *back;
// 	char *next;
	
// 	if ((str[i] == '&' || str[i] == '|') && i == 0)
// 	{
// 		printf("Syntax error : Syntax error\n");
// 		return (-1);
// 	}
// 	else if (str[i] == '&' || str[i] == '|')
// 	{
// 		back = back_str(str, i);
// 		next = next_str(str, i);
// 	}
// 	i += strlen(next);
// 	return(i);
// }