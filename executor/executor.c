/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:41:03 by mlongo            #+#    #+#             */
/*   Updated: 2023/10/18 17:54:38 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tree/tree.h"
void printTree(t_tree *node, int level, char *message);

#include "executor.h"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

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
		if (have_inputs(redir_list))
			if (execute_redirections_input(redir_list, curr_in))
				exit (1);
	}
	else
		dup_std_fd(curr_in, STDIN_FILENO);
	if (simple_cmd->redir_list != NULL)
	{
		// redir_list = (t_token *)simple_cmd->redir_list;
		// if (have_outputs(redir_list))
		// 	if (execute_redirections_output(redir_list, curr_out))
		// 		exit (1); sembra funzionare
	}
	else
		dup_std_fd(curr_out, STDOUT_FILENO);
	if (simple_cmd->cmd == NULL)
		exit (0);
	else
		execve_cmd(simple_cmd);
}

void	process_integrated(t_tree *tree, int curr_in, int curr_out)
{
	int	pid;
	int	exit_status;

	signal(SIGQUIT, ign);
	signal(SIGINT, ign);
	signal(SIGTERM, ign);
	pid = fork();
	if(pid == 0)
		execute_integrated(tree, curr_in, curr_out);
	else
	{
		signal(SIGINT, signal_handler_execve);
		signal(SIGQUIT, signal_handler_execve);
		waitpid(pid, &exit_status, 0);
		signal(SIGINT, signal_handler);
		signal(SIGTERM, signal_handler);
		signal(SIGQUIT, ign);
		if (WIFEXITED(exit_status))
			last_exit_status_cmd = WEXITSTATUS(exit_status);
		// printf("last = %d", last_exit_status_cmd);
	}
}

int	is_builtin_command(t_tree *root)
{
	t_simple_cmd	*simple_cmd;
	char			*simple_name;

	simple_cmd = (t_simple_cmd	*)root->content;
	if (simple_cmd->env)
		return 1;
	if (simple_cmd->cmd)
	{
		printf("entrato dove non dovrebbe\n");
		simple_name = (char *)simple_cmd->cmd->cmd_name->value;
		printf("valore letto %s\n", simple_name);
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
	printf("uscito in maniera corretta?\n");
	return (0);
}

void	execute_builtin_env(t_token *env)
{
	if (env->token == ENV_VAR_DECL)
		ft_export(env->value);
	if (env->token == ENV_VAR_UNSET)
		ft_unset((t_declaration *)env->value);
}

//parte da collegare con la mia
/*
	il piano:
	in pratica devo gestire bene e giocare con
	l'env fornitomi da Manuele che funziona in una maniera
	abbastanza particolare
	infatti questo environment è statico ciò significa che per utilizzarlo me
	lo devo sempre salvare questo env viene inizializzato solo una volta visto che
	è statico non c'è bisogno di ripetere l'azione 0, la quale verrà inizializzata a modo
	mio di conseguenza non si punterà al valore envp e non avremo problemi con l'env originale.
	quindi cosa famo
	1) finisco di aggiustare cd per collegarlo con l'interpretazione di manu (fatto)
	2) cambio l'inizializzazione di env all'interno della funzione env_container di manu
		perché se no faccio un macello e cd non funzionerà (fatto)
	3) controllo che cd funzioni per vedere se ho fatto le cose corrette (fatto)
	4) scelgo la prossima builtin da modificare (fatto)
*/
void	execute_builtin_cmd(t_cmd *cmd)
{
	char	**args;

	if (cmd->cmd_arg)
		args = cmd->cmd_arg->value;
	else
		args = NULL;
	if (ft_strcmp(cmd->cmd_name->value, "echo") == 0)
		ft_echo(args);
	if (ft_strcmp(cmd->cmd_name->value, "cd") == 0)
		ft_cd(args);
	if (ft_strcmp(cmd->cmd_name->value, "pwd") == 0)
		ft_pwd();
	if (ft_strcmp(cmd->cmd_name->value, "exit") == 0)
		ft_exit(args);
	if (ft_strcmp(cmd->cmd_name->value, "env") == 0)
		ft_env();
}

void	execute_builtin(t_tree *tree, int curr_in, int curr_out)
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
			if (execute_redirections_input(redir_list, curr_in))
				exit (1);
	}
	else
		dup_std_fd(curr_in, STDIN_FILENO);
	if (simple_cmd->redir_list != NULL)
	{
		redir_list = (t_token *)simple_cmd->redir_list;
		if (have_outputs(redir_list))
			if (execute_redirections_output(redir_list, curr_out))
				exit (1);
	}
	else
		dup_std_fd(curr_out, STDOUT_FILENO);
	if (simple_cmd->cmd == NULL)
	{
		if (simple_cmd->env != NULL)
			execute_builtin_env(simple_cmd->env);
	}
	else
		execute_builtin_cmd(simple_cmd->cmd);
	dup_std_fd(starting_in, STDIN_FILENO);
	dup_std_fd(starting_out, STDOUT_FILENO);
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
		execute(root->right, piping[0], curr_out);
		exit(last_exit_status_cmd);
	}
	close(piping[0]);
	close(piping[1]);
	waitpid(pid_left, &exit_status, 0);
	waitpid(pid_right, &exit_status, 0);
	last_exit_status_cmd = WEXITSTATUS(exit_status);
}

void	execute_and_op(t_tree *tree, int curr_in, int curr_out)
{
	if (!tree)
		return ;
	execute(tree->left, curr_in, curr_out);
	if (last_exit_status_cmd == 0)
		execute(tree->right, curr_in, curr_out);
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
			if (have_inputs(redir_list))
				if (execute_redirections_input(redir_list, in))
					exit (1);
		}
		else
			dup_std_fd(in, STDIN_FILENO);
		if (parenthesis_node->redir_list != NULL)
		{
			redir_list = (t_token *)parenthesis_node->redir_list;
			if (have_outputs(redir_list))
				if (execute_redirections_output(redir_list, out))
					exit (1);
		}
		else
			dup_std_fd(out, STDOUT_FILENO);
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
	signal(SIGINT, ign);
	if (tree->type == PARENTHESI)
		execute_subshell(tree, curr_in, curr_out);
	else
	execute_shell(tree, curr_in, curr_out);
}
