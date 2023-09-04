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

	i = 0;
	expected_cmd_name = 1;
	expected_cmd_arg = 0;
	while (splitcmd[i])
	{
		if (strchr(splitcmd[i], '=') && ft_isalpha(splitcmd[i][0]))
			printf("ENV_DECL ");
		else if (strchr(splitcmd[i], '*'))
			printf("WILDCARD ");
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
			printf("\nminishell: %s: command not found\n", splitcmd[i]);
			return ;
		}
		i++;
	}
	printf("\n");
}
