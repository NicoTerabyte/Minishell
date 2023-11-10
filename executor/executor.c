/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:41:03 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/10 16:31:24 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	execute_or_op(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	if (!tree)
		return ;
	execute(tree->left, curr_in, curr_out, mini);
	if (g_last_exit_status_cmd == 1)
		execute(tree->right, curr_in, curr_in, mini);
}

void	execute_operator(t_tree *tree, int curr_in, int curr_out, t_mini *mini)
{
	char	*operator;

	if (!tree)
		return ;
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
			{
				if (execute_redirections_input(redir_list, in, mini))
				{
					free_matrix(((t_mini *)var_container(NULL,
								NULL, NULL, GET_MINI))->splitcmd);
					ft_free_all(var_container(NULL, NULL, NULL,
							GET_TOKENS), var_container(NULL,
							NULL, NULL, GET_TREE));
					free_env(var_container(NULL, NULL, NULL, GET_MINI));
					exit(1);
				}
			}
		}
		else
			dup_std_fd(in, STDIN_FILENO);
		if (parenthesis_node->redir_list != NULL)
		{
			redir_list = (t_token *)parenthesis_node->redir_list;
			if (have_outputs(redir_list))
			{
				if (execute_redirections_output(redir_list, out, mini))
				{
					free_matrix(((t_mini *)var_container(NULL,
								NULL, NULL, GET_MINI))->splitcmd);
					ft_free_all(var_container(NULL, NULL, NULL,
							GET_TOKENS), var_container(NULL,
							NULL, NULL, GET_TREE));
					free_env(var_container(NULL, NULL, NULL, GET_MINI));
					exit(1);
				}
			}
		}
		else
			dup_std_fd(out, STDOUT_FILENO);
		execute(parenthesis_node->tree, in, out, mini);
		ft_free_all(var_container(NULL, NULL, NULL,
				GET_TOKENS), var_container(NULL,
				NULL, NULL, GET_TREE));
		free_matrix(((t_mini *)var_container(NULL,
					NULL, NULL, GET_MINI))->splitcmd);
		free_env(var_container(NULL, NULL, NULL, GET_MINI));
		exit(g_last_exit_status_cmd);
	}
	waitpid(subshell_pid, &subshell_exit_status, 0);
	g_last_exit_status_cmd = WEXITSTATUS(subshell_exit_status);
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
