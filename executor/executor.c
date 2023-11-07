/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:41:03 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/07 16:59:32 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void expander_env(t_declaration *env, t_mini *mini)
{
	while (env)
	{
		env->name = ft_wildcard(env->name, mini);
		if (env->value)
			env->value = ft_wildcard(env->value, mini);
		env = env->next;
	}
}

void	execute_builtin(t_tree *tree, int curr_in, int curr_out, t_mini *mini) //diff numero 2
{

	t_simple_cmd	*simple_cmd;
	t_token			*redir_list;
	int				starting_in;
	int				starting_out;

	if (!tree)
		return ;
	starting_in = curr_in;
	starting_out = curr_out;
	simple_cmd = (t_simple_cmd	*)tree->content;
	if (simple_cmd->redir_list != NULL)
	{
		redir_list = (t_token *)simple_cmd->redir_list;
		if (have_inputs(redir_list))
			if (execute_redirections_input(redir_list, curr_in, mini))
				exit (1);
	}
	else
		dup_std_fd(curr_in, STDIN_FILENO);
	if (simple_cmd->redir_list != NULL)
	{
		redir_list = (t_token *)simple_cmd->redir_list;
		if (have_outputs(redir_list))
			if (execute_redirections_output(redir_list, curr_out, mini))
				exit (1);
	}
	else
		dup_std_fd(curr_out, STDOUT_FILENO);
	if (simple_cmd->cmd == NULL)
	{
		if (simple_cmd->env != NULL)
		{
			expander_env(simple_cmd->env->value, mini);
			execute_builtin_env(simple_cmd->env, mini);
		}
	}
	else
	{
		if (simple_cmd->cmd->cmd_arg)
			expander_simple_cmd_args(simple_cmd->cmd->cmd_arg->value, mini);
		execute_builtin_cmd(simple_cmd->cmd, mini);
	}
	dup_std_fd(starting_in, STDIN_FILENO);
	dup_std_fd(starting_out, STDOUT_FILENO);
}

void	execute_simple_cmd(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	if (is_builtin_command(tree, mini))
		execute_builtin(tree, curr_in, curr_out, mini);
	else
		process_integrated(tree, curr_in, curr_out, mini);
}

void	execute_pipe_op(t_tree *root, int curr_in, int curr_out, t_mini *mini)
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
		execute(root->left, curr_in, piping[1], mini);
		exit(last_exit_status_cmd);
	}
	// waitpid(pid_left, &exit_status, 0);
	// last_exit_status_cmd = WEXITSTATUS(exit_status);
	// if (last_exit_status_cmd == 130 || last_exit_status_cmd == 131)
	// {
	// 	close(piping[0]);
	// 	close(piping[1]);
	// 	return ;
	// }
	pid_right = fork();
	if (!pid_right)
	{
		close(piping[1]);
		execute(root->right, piping[0], curr_out, mini);
		exit(last_exit_status_cmd);
	}
	close(piping[0]);
	close(piping[1]);
	waitpid(pid_left, &exit_status, 0);
	waitpid(pid_right, &exit_status, 0);
	last_exit_status_cmd = WEXITSTATUS(exit_status);
}

void	execute_and_op(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	execute(tree->left, curr_in, curr_out, mini);
	if (last_exit_status_cmd == 0)
		execute(tree->right, curr_in, curr_out, mini);
}

void	execute_or_op(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	execute(tree->left, curr_in, curr_out, mini);
	if (last_exit_status_cmd == 1)
		execute(tree->right, curr_in, curr_in, mini);
}

void	execute_operator(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	char	*operator;

	operator = (char *)tree->content;
	if (!ft_strcmp(operator, "&&"))
		execute_and_op(tree, curr_in, curr_out, mini);
	else if (!ft_strcmp(operator, "||"))
		execute_or_op(tree, curr_in, curr_out, mini);
	else
		execute_pipe_op(tree, curr_in, curr_out, mini);
}

static void	execute_subshell(t_tree *root, int in, int out, t_mini *mini)
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
			if (have_inputs(redir_list))
				if (execute_redirections_input(redir_list, in, mini))
					exit (1);
		}
		else
			dup_std_fd(in, STDIN_FILENO);
		if (parenthesis_node->redir_list != NULL)
		{
			redir_list = (t_token *)parenthesis_node->redir_list;
			if (have_outputs(redir_list))
				if (execute_redirections_output(redir_list, out, mini))
					exit (1);
		}
		else
			dup_std_fd(out, STDOUT_FILENO);
		execute(parenthesis_node->tree, in, out, mini);
		exit(last_exit_status_cmd);
	}
	waitpid(subshell_pid, &subshell_exit_status, 0);
	last_exit_status_cmd = WEXITSTATUS(subshell_exit_status);
}

void	execute_shell(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	else if (tree->type == SIMPLE_CMD)
		execute_simple_cmd(tree, curr_in, curr_out, mini);
	else
		execute_operator(tree, curr_in, curr_out, mini);
}

void	execute(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	signal(SIGINT, ign);
	if (tree->type == PARENTHESI)
		execute_subshell(tree, curr_in, curr_out, mini);
	else
	execute_shell(tree, curr_in, curr_out, mini);
}
