/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 13:37:51 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/22 12:34:54 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "../tree/tree.h"
# include <sys/types.h>
# include <sys/wait.h>
# include "../minishell.h"

void	execute(t_tree *tree, int curr_in, int curr_out);

#endif
