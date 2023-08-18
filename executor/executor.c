/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:41:03 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/18 18:57:02 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"

void	dup_std_fd(int cur_in_out, int std_in_out)
{
	if (cur_in_out != std_in_out)
	{
		dup2(cur_in_out, std_in_out);
		close(cur_in_out);
	}
}

int	execute_redirections(t_token *redir_list, int curr_in, int curr_out)
{
	char *file_name;

	if (curr_in != STDIN_FILENO)
		close(curr_in);
	while (redir_list)
	{
		file_name = (char *)redir_list->value;
		if (redir_list->token == IN_FILE_TRUNC || redir_list->token == HERE_DOC)
			curr_in = open(file_name, O_RDONLY);
		else if (redir_list->token == OUT_FILE_TRUNC)
			curr_out = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0777);
		else
			curr_out = open(file_name, O_CREAT | O_APPEND | O_WRONLY, 0777);
		if (curr_in == -1 || curr_out == -1)
			return (1);
	}
	dup_std_fd(curr_in, STDIN_FILENO);
	dup_std_fd(curr_out, STDOUT_FILENO);
	return (0);
}

void	execute_integrated(t_tree *tree, int curr_in, int curr_out)
{
	t_simple_cmd	*simple_cmd;
	t_token			*redir_list;

	if (!tree)
		return ;
	simple_cmd = (t_simple_cmd	*)tree->content;
	if (simple_cmd->redir_list != NULL)
	{
		redir_list = (t_token *)simple_cmd->redir_list;
		if (!execute_redirections(redir_list, curr_in, curr_out))
		{
			perror("minishell :");
			exit(1);
		}
	}
	if (simple_cmd->cmd == NULL)
		exit (0);
	else
		execve_cmd(simple_cmd);
}

void	process_integrated(t_tree *tree, int curr_in, int curr_out)
{
	int	pid;
	int	exit_status;

	pid = fork();
	if(pid == 0)
		process_integrated(tree, curr_in, curr_out);
	else
		waitpid(pid, &exit_status, 0);
	if (WIFEXITED(exit_status))
			last_exit_status_cmd = WEXITSTATUS(exit_status);
}

int	is_builtin_command(t_tree *root)
{
	t_simple_cmd	*simple_cmd;
	char			*simple_name;


	simple_cmd = (t_simple_cmd	*)root->content;
	if (simple_cmd->cmd->cmd_name == NULL)
	{
		if (simple_cmd->env == NULL)
			return (0);
		return (1);
	}
	simple_name = (char *)simple_cmd->cmd->cmd_name;
	if (0 == ft_strcmp(simple_name, "cd")
		|| 0 == ft_strcmp(simple_name, "exit")
		|| 0 == ft_strcmp(simple_name, "echo")
		|| 0 == ft_strcmp(simple_name, "pwd")
		|| 0 == ft_strcmp(simple_name, "env")
	)
		return (1);
	else
		return (0);
}

void	execute_simple_cmd(t_tree *tree, int curr_in, int curr_out)
{
	if (!tree)
		return ;
	if (is_builtin_command(tree))
		execute_builtin(tree, curr_in, curr_out);
	else
		process_integrated(tree, curr_in, curr_out);
}

void	execute_shell(t_tree *tree, int curr_in, int curr_out)
{
	if (!tree)
		return ;
	else if (tree->type == SIMPLE_CMD)
		execute_simple_cmd(tree, curr_in, curr_out);
	else
		execute_operator(tree, curr_in, curr_out);
}

void	execute(t_tree *tree, int curr_in, int curr_out)
{
	if (!tree)
		return ;
	else if (tree->type == PARENTHESI)
		execute_subshell(tree, curr_in, curr_out);
	else
		execute_shell(tree, curr_in, curr_out);
}
