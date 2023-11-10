/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:30:58 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/10 16:31:18 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander_env(t_declaration *env, t_mini *mini)
{
	while (env)
	{
		env->name = expander(mini, env->name);
		if (env->value)
			env->value = expander(mini, env->value);
		env = env->next;
	}
}

void	execute_builtin(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	t_simple_cmd	*simple_cmd;
	t_token			*redir_list;
	int				starting_in;
	int				starting_out;

	if (!tree)
		return ;
	starting_in = dup(fileno(stdin));
	starting_out = dup(fileno(stdout));
	simple_cmd = (t_simple_cmd *)tree->content;
	if (simple_cmd->redir_list != NULL)
	{
		redir_list = (t_token *)simple_cmd->redir_list;
		if (have_inputs(redir_list))
		{
			if (execute_redirections_input(redir_list, curr_in, mini))
			{
				g_last_exit_status_cmd = 1;
				return ;
			}
		}
	}
	else
		dup_std_fd(curr_in, STDIN_FILENO);
	if (simple_cmd->redir_list != NULL)
	{
		redir_list = (t_token *)simple_cmd->redir_list;
		if (have_outputs(redir_list))
		{
			if (execute_redirections_output(redir_list, curr_out, mini))
			{
				g_last_exit_status_cmd = 1;
				return ;
			}
		}
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

void	execute_simple_cmd(t_tree *tree, int curr_in,
			int curr_out, t_mini *mini)
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
		ft_free_all(var_container(NULL, NULL,
				NULL, GET_TOKENS), var_container(NULL, NULL, NULL, GET_TREE));
		free_matrix(((t_mini *)var_container(NULL,
					NULL, NULL, GET_MINI))->splitcmd);
		free_env(var_container(NULL, NULL, NULL, GET_MINI));
		exit(g_last_exit_status_cmd);
	}
	pid_right = fork();
	if (!pid_right)
	{
		close(piping[1]);
		execute(root->right, piping[0], curr_out, mini);
		ft_free_all(var_container(NULL, NULL, NULL,
				GET_TOKENS), var_container(NULL, NULL, NULL, GET_TREE));
		free_matrix(((t_mini *)var_container(NULL,
					NULL, NULL, GET_MINI))->splitcmd);
		free_env(var_container(NULL, NULL, NULL, GET_MINI));
		exit(g_last_exit_status_cmd);
	}
	close(piping[0]);
	close(piping[1]);
	waitpid(pid_left, &exit_status, 0);
	waitpid(pid_right, &exit_status, 0);
	g_last_exit_status_cmd = WEXITSTATUS(exit_status);
}

void	execute_and_op(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	execute(tree->left, curr_in, curr_out, mini);
	if (g_last_exit_status_cmd == 0)
		execute(tree->right, curr_in, curr_out, mini);
}
