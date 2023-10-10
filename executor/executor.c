/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:41:03 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/22 19:22:16 by mlongo           ###   ########.fr       */
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
	char	*file_name;

	if (curr_in != STDIN_FILENO)
		close(curr_in);
	if (curr_out != STDOUT_FILENO)
		close(curr_out);
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
		{
			printf("minishell : %s: No such file or directory\n", file_name);
			return (1);
		}
		redir_list = redir_list->next;
	}
	dup_std_fd(curr_in, STDIN_FILENO);
	dup_std_fd(curr_out, STDOUT_FILENO);
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

char	*get_cmd_name_path(char *cmd_name, char **split_paths)
{
	char	*path;
	int		i;
	char	*tmp;

	i = 0;
	if (access(cmd_name, X_OK) == 0)
		return (cmd_name);
	while (split_paths[i])
	{
		path = ft_strjoin(split_paths[i], "/");
		tmp = path;
		path = ft_strjoin(path, cmd_name);
		free(tmp);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}

void	execve_cmd(t_simple_cmd *simple_cmd)
{
	char	**env;
	char	**split_paths;
	char	*cmd_name;
	char	**cmd_args;

	env = env_container(1, NULL);
	split_paths = get_paths(env);
	split_paths[0] = ft_strtrim(split_paths[0], "PATH=");
	cmd_name = get_cmd_name_path((char *)simple_cmd->cmd->cmd_name->value, split_paths);
	if (cmd_name == NULL)
	{
		printf("minishell : %s command not found\n", (char *)simple_cmd->cmd->cmd_name->value);
		exit(1);
	}
	cmd_args = get_cmd_args(simple_cmd);
	execve(cmd_name, cmd_args, env);
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
		if (execute_redirections(redir_list, curr_in, curr_out))
			exit (1);
	}
	else
	{
		dup_std_fd(curr_in, STDIN_FILENO);
		dup_std_fd(curr_out, STDOUT_FILENO);
	}
	if (simple_cmd->cmd->cmd_name == NULL)
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
		execute_integrated(tree, curr_in, curr_out);
	else
	{
		waitpid(pid, &exit_status, 0);
		if (WIFEXITED(exit_status))
			last_exit_status_cmd = WEXITSTATUS(exit_status);
		handle_here_doc(NULL, NULL);
	}
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
		// execute_builtin(tree, curr_in, curr_out);
		;
	else
		process_integrated(tree, curr_in, curr_out);
}

void	execute_pipe_op(t_tree *root, int curr_in, int curr_out)
{
	int	piping[2];
	int	pid_left;
	int	pid_right;
	int	exit_status;

	pipe(piping);
	pid_left = fork();
	if (!pid_left)
	{
		close(piping[0]);
		execute(root->left, curr_in, piping[1]);
		exit(last_exit_status_cmd);
	}
	pid_right = fork();
	if (!pid_right)
	{
		close(piping[1]);
		execute(root->right, piping[0], curr_out);
		exit(last_exit_status_cmd);
	}
	close(piping[0]);
	close(piping[1]);
	waitpid(pid_left, NULL, 0);
	waitpid(pid_right, &exit_status, 0);
	last_exit_status_cmd = WEXITSTATUS(exit_status);
}

void	execute_and_op(t_tree *tree, int curr_in, int curr_out)
{
	if (!tree)
		return ;
	execute(tree->left, curr_in, curr_out);
	if (last_exit_status_cmd == 0)
		execute(tree->right, curr_in, curr_in);
}

void	execute_or_op(t_tree *tree, int curr_in, int curr_out)
{
	if (!tree)
		return ;
	execute(tree->left, curr_in, curr_out);
	if (last_exit_status_cmd == 1)
		execute(tree->right, curr_in, curr_in);
}

void	execute_operator(t_tree *tree, int curr_in, int curr_out)
{
	if (!tree)
		return ;
	char	*operator;

	operator = (char *)tree->content;
	if (!ft_strcmp(operator, "&&"))
		execute_and_op(tree, curr_in, curr_out);
	else if (!ft_strcmp(operator, "||"))
		execute_or_op(tree, curr_in, curr_out);
	else
		execute_pipe_op(tree, curr_in, curr_out);
}

static void	execute_subshell(t_tree *root, int in, int out)
{
	int				subshell_pid;
	int				subshell_exit_status;
	t_parenthesis	*parenthesis_node;
	t_token			*redir_list;

	parenthesis_node = (t_parenthesis *)root->content;
	subshell_pid = fork();
	if (subshell_pid == 0)
	{
		if (parenthesis_node->redir_list != NULL)
		{
			redir_list = (t_token *)parenthesis_node->redir_list;
			if (execute_redirections(redir_list, in, out))
				exit (1);
		}
		else
		{
			dup_std_fd(in, STDIN_FILENO);
			dup_std_fd(out, STDOUT_FILENO);
		}
		execute(parenthesis_node->tree, in, out);
		exit(last_exit_status_cmd);
	}
	waitpid(subshell_pid, &subshell_exit_status, 0);
	last_exit_status_cmd = WEXITSTATUS(subshell_exit_status);
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
