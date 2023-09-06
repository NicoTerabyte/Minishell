#include "lexer.h"

int	count_syntax(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i + 1] && ((str[i] == '|' && str[i + 1] == '|') || (str[i] == '&' && str[i + 1] == '&') || (str[i] == '<' && str[i + 1] == '<') || (str[i] == '>' && str[i + 1] == '>')))
		{
			if (i != 0 && str[i - 1] != ' ')
				count++;
			if (str[i + 2] && str[i + 2] != ' ')
				count++;
		}
		else if (ft_strchr("|()<>", str[i]))
		{
			if (i != 0 && str[i - 1] != ' ')
				count++;
			if (str[i + 1] && str[i + 1] != ' ')
				count++;
		}
		i++;
	}
	return (i + count);
}

int	ft_isspace(char c)
{
	return (c == 32 || (c >= '\t' && c <= '\r'));
}

char	*fix_white_spaces(char *str)
{
	int		i;
	int		j;
	char 	*res;

	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	res = malloc(ft_strlen(str));
	while (str[i])
	{
		if (ft_isspace(str[i]) && ft_isspace(str[i + 1]))
			i++;
		else
			res[j++] = str[i++];
	}
	res[j] = 0;
	free(str);
	return (res);
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
	res = fix_white_spaces(res);
	return (res);
}
