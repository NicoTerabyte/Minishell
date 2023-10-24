/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:37:51 by mlongo            #+#    #+#             */
/*   Updated: 2023/10/24 18:14:13 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../tree/tree.h"
# include "../lexer/lexer.h"
# include <sys/types.h>
# include <sys/wait.h>
# include "../minishell.h"
# include "../builtins/builtins.h"
# include <signal.h>
# include <stdio.h>
# include <sys/types.h>
# include <unistd.h>

void	execute(t_tree *tree, int curr_in, int curr_out, t_mini *mini);
void	redir_simple_command(t_token *r_list, t_simple_cmd *sim_cmd, int curr_out);
int		have_outputs(t_token *redir_list);
int		execute_redirections_output(t_token *redir_list, int curr_out);
void	dup_std_fd(int cur_in_out, int std_in_out);
int		execute_redirections_input(t_token *redir_list, int curr_in);
char	**get_paths(char **env);
char	**get_cmd_args(t_simple_cmd *simple_cmd);
char	*get_cmd_name_path(char *cmd_name, char **split_paths);
void	signal_handler_execve(int signum);
int		have_inputs(t_token *redir_list);
int		have_outputs(t_token *redir_list);
void	execve_cmd(t_simple_cmd *simple_cmd, t_mini *mini);
#endif
