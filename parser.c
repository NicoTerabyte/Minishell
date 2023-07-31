#include "minishell.h"

int	cmd_name(char *str)
{
	int i;
	char	**path;
	char	*s;
	char	*tmp;

	i = -1;
	if (!ft_strcmp(str, "pwd") || !ft_strcmp(str, "echo") || !ft_strcmp(str, "cd")
		|| !ft_strcmp(str, "exit") || !ft_strcmp(str, "env")
		|| !ft_strcmp(str, "unset") || !ft_strcmp(str, "export"))
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

void	parser(char **splitcmd)
{
	int i;
	int expected_cmd_name;
	int expected_cmd_arg;
	int	j;
	int indouble;
	int closedquotes;

	closedquotes = 0;
	indouble = 0;
	j = 0;
	i = 0;
	expected_cmd_name = 1;
	expected_cmd_arg = 0;

	char *tmp = NULL;
	while (splitcmd[i])
	{
		// printf ("%s\n", splitcmd[i]);
		if (strchr(splitcmd[i], '=') && ft_isalpha(splitcmd[i][0]))
			printf("ENV_DECL ");
		else if (strchr(splitcmd[i], '*'))
			printf("WILDCARD ");
		else if (strchr(splitcmd[i], '"') || strchr(splitcmd[i], '\''))
		{
			tmp = strchr(splitcmd[i], '"') + 1;
			while (strchr(tmp, '"'))
			{
				// if (strchr(splitcmd[i], '"') < strchr(splitcmd[i], '\''))
				// 	indouble = 1;
				// tmp = strchr(splitcmd[i], '"') + 1;
				// if (indouble)
				// {
				printf("DOUBLE_QUOTES ");
				if ((strchr(tmp + 1, '"')))
				{
					tmp = strchr(tmp + 1, '"') + 1;
					closedquotes = 0;
				}
				else
					closedquotes = 1;
				// if ((strchr(tmp, '"') + 1) != NULL)
				// {
				// 	tmp = strchr(tmp, '"') + 1;
				// 	if (*tmp)
				// 	{
				// 		if ((strchr(tmp, '"') + 1) != NULL)
				// 		{
				// 			tmp = strchr(tmp, '"') + 1;
				// 			closedquotes = 0;
				// 		}
				// 	}
				// }
				// }
				// else
				// {
				// 	if (strchr(tmp, '\''))
				// 		printf("SINGLE_QUOTES ");
				// 	else
				// 	{
				// 		printf("minishell : unclosed quotes\n");
				// 		return;
				// 	}
				// 	tmp = strchr(tmp, '\'');
				// }
			}
			if (!closedquotes)
				printf("minishell : unclosed quotes");
		}
		else if (splitcmd[i][0] == '$' && splitcmd[i][1] != ' ' && splitcmd[i][1] != 0)
			printf("EXPANSION ");
		else if (!strcmp(splitcmd[i], ")"))
			printf("parenthesis_closed ");
		else if (!strcmp(splitcmd[i], "("))
		{
			printf("parenthesys_open ");
			expected_cmd_name = 1;
			expected_cmd_arg = 0;
		}
		else if (!strcmp(splitcmd[i], "<"))
		{
			printf("redirect_input file_input ");
			i++;
		}
		else if (!strcmp(splitcmd[i], ">"))
		{
			printf("redirect_output_trunc file_output_trunc ");
			i++;
		}
		else if (!strcmp(splitcmd[i], "<<"))
		{
			printf("here_doc delimiter ");
			i++;
		}
		else if (!strcmp(splitcmd[i], ">>"))
		{
			printf("redirect_output_append file_output_append ");
			i++;
		}
		else if (cmd_name(splitcmd[i]) && expected_cmd_name && !expected_cmd_arg)
		{
			printf("cmd_name ");
			expected_cmd_name = 0;
			expected_cmd_arg = 1;
		}
		else if (i != 0 && !strcmp(splitcmd[i], "&&") && !expected_cmd_name)
		{
			printf("AND ");
			expected_cmd_name = 1;
			expected_cmd_arg = 0;
		}
		else if (i != 0 && !strcmp(splitcmd[i], "||") && !expected_cmd_name)
		{
			printf("OR ");
			expected_cmd_name = 1;
			expected_cmd_arg = 0;
		}
		else if (i != 0 && !strcmp(splitcmd[i], "|") && !expected_cmd_name)
		{
			printf("PIPE ");
			expected_cmd_name = 1;
			expected_cmd_arg = 0;
		}
		else if (!expected_cmd_name && expected_cmd_arg)
			printf("cmd_arg ");
		else
		{
			printf(" minishell: %s: command not found\n", splitcmd[i]);
			return ;
		}
		i++;
	}
	printf("\n");
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

char	*fix_syntax(char *str)
{
	int		i;
	int		j;
	char	*res;

	i = 0;
	j = 0;
	res = malloc(count_syntax(str));
	while (str[i])
	{
		if (str[i + 1] && ((str[i] == '|' && str[i + 1] == '|') || (str[i] == '&' && str[i + 1] == '&')
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
