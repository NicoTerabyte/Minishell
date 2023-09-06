#include "lexer.h"

// static t_list	*start_back(t_list *here_doc_lst)
// {
// 	while (here_doc_lst && here_doc_lst->prev)
// 		here_doc_lst = here_doc_lst->prev;
// 	return (here_doc_lst);
// }

// static void	del(void *str)
// {
// 	free(str);
// }

// static void	*handle_list_heredocs(int op)
// {
// 	static t_list	*here_doc_lst;
// 	char			*here_doc;

// 	if (op == START)
// 	{
// 		here_doc_lst = start_back(here_doc_lst);
// 		ft_lstclear(&here_doc_lst, &del);
// 		here_doc_lst = NULL;
// 	}
// 	else if (op == ADD)
// 	{
// 		here_doc = here_doc_name();
// 		ft_lstadd_back(&here_doc_lst, ft_lstnew(here_doc));
// 		return (here_doc);
// 	}
// 	else if (op == LIST)
// 		return (here_doc_lst);
// 	else if (op == GET)
// 	{
// 		return (here_doc_lst->content);
// 		if (here_doc_lst->next)
// 			here_doc_lst = here_doc_lst->next;
// 	}
// 	return (NULL);
// }

// static void handle_here_doc_sig(int signum)
// {
// 	(void)signum;
// 	exit(130);
// }

// static int	reading(int fd, char *del)
// {
// 	char	*str;

// 	signal(SIGINT, handle_here_doc_sig);
// 	while (1)
// 	{
// 		str = readline("heredoc> ");
// 		if (str == NULL)
// 		{
// 			printf("\n");
// 			free(str);
// 			free(del);
// 			exit(0);
// 		}
// 		if (ft_strcmp(str, del) == 0)
// 			break ;
// 		//esp str
// 		write(fd, str, ft_strlen(str));
// 		free(str);
// 	}
// 	printf("ok\n");
// 	free(str);
// 	free(del);
// 	exit(0);
// }

// static void	handle_here_doc(char *del)
// {
// 	char	*here_doc;
// 	int		fd;
// 	int		pid;
// 	int		exit_status;

// 	//esp del
// 	here_doc = handle_list_heredocs(ADD);
// 	fd = open(here_doc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 	pid = fork();
// 	if (!pid)
// 		reading(fd, del);
// 	waitpid(pid, &exit_status, 0);
// 	free(del);
// 	last_exit_status_cmd = WEXITSTATUS(exit_status);
// 	close(fd);
// }

int	check(char *s)
{
	int	i;

	i = 0;
	if (!check_bad_parentheses(s, i))
		return (0);
	while (s[i])
	{
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
			// if (s[i] == '<' && s[i + 1] == '<')
			// 	handle_here_doc(create_del(&s[i + 3]));
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

int check_bad_parentheses(char *s, int i)
{
	while (s[i] && s[i] != '(')
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
		if (s[i] == ')')
			return (0);
		i++;
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

// char	*create_del(char *s)
// {
// 	char	quote;
// 	int		i;

// 	i = 0;
// 	while (s[i] && !isspace(s[i]))
// 	{
// 		if (s[i] == '"' || s[i] == '\'')
// 		{
// 			quote = s[i];
// 			while (s[i] && s[i] != quote)
// 				i++;
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (ft_substring((s, 0, i)));
// }
