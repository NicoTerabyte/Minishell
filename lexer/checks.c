#include "../minishell.h"

char	*create_del(char *s)
{
	char	quote;
	int		i;

	i = 0;
	while (s[i] && !ft_isspace(s[i]))
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i];
			while (s[i] && s[i] != quote)
				i++;
			break ;
		}
		i++;
	}
	return (ft_substr(s, 0, i));
}

int	check(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ')')
		{
			if (!check_number_back(&s[i], &s[0]))
				return (0);
		}
		if (s[i] == '(')
		{
			if (!check_parentheses(s, &i))
				return (0);
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			if (!check_quote(s))
				return (0);
		}
		else if ((s[i] == '&' && s[i + 1] == '&') || s[i] == '|' || s[i] == '>' || s[i] == '<')
		{
			if (!check_operator(s, &i))
				return (0);
			if (s[i] == '<' && s[i + 1] == '<')
			{
					handle_here_doc(create_del(&s[i + 3]));
					if (last_exit_status_cmd == 130)
						return (0);
			}
		}
		i++;
	}
	return (1);
}

