/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:44:33 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/22 19:12:40 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char *no_quotes(char *str)
{
	char	*res;
	int		i;
	int		j;
	int		diff;

	diff = 0;
	i = 0;
	j = 0;
	res = ft_substr(str, 0, ft_strlen(str));
	while (str[i])
	{
		if (str[i] == '"')
		{
			diff = ft_strlen(str) - ft_strlen(res);
			j = i;
			i++;
			while (str[j + 1])
			{
				res[j - diff] = str[j + 1];
				j++;
			}
			res[j - diff] = 0;
			while (str[i] != '"')
				i++;
			diff = ft_strlen(str) - ft_strlen(res);
			j = i;
			i++;
			while (str[j + 1])
			{
				res[j - diff] = str[j + 1];
				j++;
			}
			res[j - diff] = 0;
		}
		else if (str[i] == '\'')
		{
			diff = ft_strlen(str) - ft_strlen(res);
			j = i;
			i++;
			while (str[j + 1])
			{
				res[j - diff] = str[j + 1];
				j++;
			}
			res[j - diff] = 0;
			while (str[i] != '\'')
				i++;
			diff = ft_strlen(str) - ft_strlen(res);
			j = i;
			i++;
			while (str[j + 1])
			{
				res[j - diff] = str[j + 1];
				j++;
			}
			res[j - diff] = 0;
		}
	}
	res[i - (ft_strlen(str) - ft_strlen(res))] = 0;
	return (res);
}

int	cmd_name(char *str)
{
	int i;
	char	**path;
	char	*s;
	char	*tmp;

	i = -1;
	if (!ft_strncmp(str, "pwd", 3) || !ft_strncmp(str, "echo", 4) || !ft_strncmp(str, "cd", 2)
		|| !ft_strncmp(str, "exit", 4) || !ft_strncmp(str, "env", 3)
		|| !ft_strncmp(str, "unset", 5) || !ft_strncmp(str, "export", 6))
		return(1);
	path = ft_split(getenv("PATH"), ':');
	if (!access(str, F_OK | R_OK))
		return (1);
	while (path[++i])
	{
		s = ft_strjoin(path[i], "/");
		tmp = s;
		s = ft_strjoin(s, str);
		free(tmp);
		if (!access(s, F_OK))
		{
			free_matrix(path);
			free(s);
			return (1);
		}
		free(s);
	}
	free_matrix(path);
	return (0);
}

int	count_syntax(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i + 1] && ((str[i] == '|' && str[i + 1] == '|') || (str[i] == '&' && str[i + 1] == '&') || (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')))
			count += 2;
		else if (ft_strchr("|()<>", str[i]))
			count += 2;
		i++;
	}
	return (i + count);
}

char	*fix_syntax(char *str)
{
	int		i;
	int		j;
	char	quote;
	char	*res;


	quote = 0;
	i = 0;
	j = 0;
	res = malloc(count_syntax(str) + 1);
	while (str[i])
	{
		if (str[i] == '"' || str[i] == '\'')
		{
			res[j++] = str[i++];
			quote = str[i];
			while (str[i] && str[i] != quote)
				res[j++] = str[i++];
			if (str[i] == quote)
				res[j++] = str[i++];
		}
		else if (str[i + 1] && ((str[i] == '|' && str[i + 1] == '|') || (str[i] == '&' && str[i + 1] == '&')
			|| (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')))
		{
			if ((i != 0 && str[i - 1] != ' ') && (str[i + 2] && str[i + 2] != ' '))
			{
				res[j++] = ' ';
				res[j++] = str[i++];
				res[j++] = str[i++];
				res[j++] = ' ';
			}
			else if (i != 0 && str[i - 1] != ' ')
			{
				res[j++] = ' ';
				res[j++] = str[i++];
				res[j++] = str[i++];
			}
			else
			{
				res[j++] = str[i++];
				res[j++] = str[i++];
				res[j++] = ' ';
			}
		}
		else if (ft_strchr("|()<>", str[i]))
		{
			if ((i != 0 && str[i - 1] != ' ') && (str[i + 1] && str[i + 1] != ' '))
			{
				res[j++] = ' ';
				res[j++] = str[i++];
				res[j++] = ' ';
			}
			else if (i != 0 && str[i - 1] != ' ')
			{
				res[j++] = ' ';
				res[j++] = str[i++];
			}
			else
			{
				res[j++] = str[i++];
				res[j++] = ' ';
			}
		}
		else
			res[j++] = str[i++];
	}
	res[j] = 0;
	return (res);
}
