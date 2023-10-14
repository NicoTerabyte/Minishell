/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:20:50 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/12 20:21:27 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void	dup_std_fd(int cur_in_out, int std_in_out)
{
	if (cur_in_out != std_in_out)
	{
		dup2(cur_in_out, std_in_out);
		close(cur_in_out);
	}
}

int	execute_redirections_output(t_token *redir_list, int curr_out)
{
	char	*file_name;

	if (curr_out != STDOUT_FILENO)
		close(curr_out);
	while (redir_list)
	{
		file_name = (char *)redir_list->value;
		if (redir_list->token == OUT_FILE_TRUNC)
			curr_out = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else if (redir_list->token == OUT_FILE_APPEND)
			curr_out = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (curr_out == -1)
		{
			printf("minishell : %s: error creting file\n", file_name);
			return (1);
		}
		redir_list = redir_list->next;
	}
	dup_std_fd(curr_out, STDOUT_FILENO);
	return (0);
}

int	execute_redirections_input(t_token *redir_list, int curr_in)
{
	char	*file_name;

	if (curr_in != STDIN_FILENO)
		close(curr_in);
	while (redir_list)
	{
		file_name = (char *)redir_list->value;
		if (redir_list->token == IN_FILE_TRUNC || redir_list->token == HERE_DOC)
			curr_in = open(file_name, O_RDONLY);
		if (curr_in == -1)
		{
			printf("minishell : %s: No such file or directory\n", file_name);
			return (1);
		}
		redir_list = redir_list->next;
	}
	dup_std_fd(curr_in, STDIN_FILENO);
	return (0);
}

char	**get_paths(char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != 0)
			break ;
		i++;
	}
	return (ft_split(env[i], ':'));
}

char	**get_cmd_args(t_simple_cmd *simple_cmd)
{
	char	**res;
	int		i;
	char	**args;

	i = 0;
	if (simple_cmd->cmd->cmd_arg != NULL)
	{
		args = (char **)simple_cmd->cmd->cmd_arg->value;
		while (args[i])
			i++;
	}
	res = (char **)malloc(sizeof(char *) * (i + 2));
	i = 1;
	res[0] = simple_cmd->cmd->cmd_name->value;
	if (simple_cmd->cmd->cmd_arg != NULL)
	{
		args = (char **)simple_cmd->cmd->cmd_arg->value;
		while (args[i - 1])
		{
			res[i] = args[i - 1];
			i++;
		}
	}
	res[i] = NULL;
	return (res);
}
