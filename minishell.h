/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alessiolongo <alessiolongo@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/18 11:35:53 by mlongo            #+#    #+#             */
/*   Updated: 2023/08/20 11:52:27 by alessiolong      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./global.h"
# include "./libft/libft.h"
# include "./gnl/get_next_line_bonus.h"
# include "./tokenizer/tokenizer.h"
# include "./tree/tree.h"
# include "./executor/executor.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>

char	**env_container(int action, void *arg);

#endif
