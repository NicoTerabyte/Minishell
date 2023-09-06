#include "lexer.h"

char	*create_del(char *s)
{
	char	quote;
	int		i;

	i = 0;
	while (s[i] && !isspace(s[i]))
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

int	check_parentheses(char *s, int *i)
{
	if (*i != 0)
	{
		if (!((s[*i - 2] == '&' && s[*i - 3] == '&') || (s[*i - 2] == '|' && s[*i - 3] == '|') || (s[*i - 2] == '|' && s[*i - 3] == ' ')))
			return (0);
	}
	if (check_number(s))
		return (1);
	return (0);
}

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

static int not_op(char *c)
{
    if ((c[0] != '|' && c[1] != '|') || (c[0] != '&' && c[1] != '&') || c[0] != '|')
        return (c[0] >= 32 && c[0] <= 126);
    return (0);
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
