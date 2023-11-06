/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:42:00 by alessiolong       #+#    #+#             */
/*   Updated: 2023/11/06 17:20:24 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*start_back(t_list *here_doc_lst)
{
	while (here_doc_lst && here_doc_lst->prev)
		here_doc_lst = here_doc_lst->prev;
	return (here_doc_lst);
}


void	*handle_list_heredocs(int op)
{
	static t_list	*here_doc_lst;
	t_list			*res;
	char			*here_doc;

	if (op == START)
	{
		here_doc_lst = start_back(here_doc_lst);
		ft_lstclear(&here_doc_lst, &del);
		here_doc_lst = NULL;
	}
	else if (op == ADD)
	{
		here_doc = here_doc_name();
		ft_lstadd_back(&here_doc_lst, ft_lstnew(here_doc));
		return (here_doc);
	}
	else if (op == LIST)
		return (start_back(here_doc_lst));
	else if (op == GET)
	{
		res = here_doc_lst;
		if (here_doc_lst->next)
			here_doc_lst = here_doc_lst->next;
		return (res->content);
	}
	return (NULL);
}

void handle_here_doc_sig(int signum)
{
	(void)signum;
	printf("\n");
	exit(130);
}

int	reading(int fd, char *del)
{
	char	*str;

	signal(SIGINT, handle_here_doc_sig);
	while (1)
	{
		str = readline("heredoc> ");
		if (str == NULL)
		{
			printf("\n");
			free(str);
			free(del);
			exit(0);
		}
		if (ft_strcmp(str, del) == 0)
			break ;
		//esp str
		write(fd, str, ft_strlen(str));
		write(fd, &"\n", 1);
		free(str);
	}
	free(str);
	free(del);
	exit(0);
}

void	handle_here_doc(char *del)
{
	char	*here_doc;
	int		fd;
	int		pid;
	int		exit_status;

	//esp del
	here_doc = handle_list_heredocs(ADD);
	fd = open(here_doc, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (!pid)
		reading(fd, del);
	waitpid(pid, &exit_status, 0);
	free(del);
	last_exit_status_cmd = WEXITSTATUS(exit_status);
	close(fd);
}
