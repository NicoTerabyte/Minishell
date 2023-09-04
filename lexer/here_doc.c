/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/02 15:42:00 by alessiolong       #+#    #+#             */
/*   Updated: 2023/09/04 15:49:51 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "../tokenizer/tokenizer.h"
#include "../global.h"

t_list	*start_back(t_list *here_doc_lst)
{
	while (here_doc_lst && here_doc_lst->prev)
		here_doc_lst = here_doc_lst->prev;
	return (here_doc_lst);
}

void	del(char *str)
{
	free(str);
}

void	*handle_list_heredocs(int op)
{
	static t_list	*here_doc_lst;
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
		return (here_doc_lst);
	else if (op == GET)
	{
		return (here_doc_lst->content);
		if (here_doc_lst->next)
			here_doc_lst = here_doc_lst->next;
	}
	return (NULL);
}

void handle_here_doc_sig(int signum)
{
	exit(1);
}

int	reading(int fd, char *del)
{
	char	*str;
	char	*del;

	del = set_del_value();
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
		if (ft_strncmp(str, del, ft_strlen(del)) == 0
			&& ft_strlen(str) == (ft_strlen(del) + 1))
			break ;
		//esp str
		write(fd, str, ft_strlen(str));
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
	pid = fork();
	if (!pid)
		reading(fd, del);
	waitpid(pid, &exit_status, 0);
	free(del);
	last_exit_status_cmd = WEXITSTATUS(exit_status);
	close(fd);
}
