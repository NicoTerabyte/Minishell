#include "../minishell.h"

int	check(char *s, t_mini *mini)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '(')
		{
			if (!check_parentheses(s, &i))
				return (0);
		}
		else if (s[i] == ')')
		{
			if (s[i + 1] != 0)
			{
				if (!is_op_or_red(s, &i + 2))
					return (0);
			}
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			if (!check_quote(s))
				return (0);
		}
		else if (is_op_or_red(s, &i) != 0)
		{
			// printf("%d\n", is_op_or_red(s, &i));
			// printf("%d\n", check_operator(s, &i));
			if (!check_operator(s, &i) || is_op_or_red(s, &i) < 0)
				return (0);
			if (s[i] == '<' && s[i + 1] == '<')
			{
					handle_here_doc(create_del(&s[i + 3]), mini);
					if (g_last_exit_status_cmd == 130)
						return (0);
			}
		}
	}
	return (1);
}
