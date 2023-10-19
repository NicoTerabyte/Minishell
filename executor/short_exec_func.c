/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   short_exec_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 20:06:33 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/12 20:17:00 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "executor.h"
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void	redir_simple_command(t_token *r_list, t_simple_cmd *sim_cmd, int curr_out)
{
	r_list = (t_token *)sim_cmd->redir_list;
		if (have_outputs(r_list))
			if (execute_redirections_output(r_list, curr_out))
				exit (1);
}
