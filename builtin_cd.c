/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:34:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/08/07 15:45:15 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **command_line, t_data *shell_data)
{
	char	*home;
	int		i;

	i = 0;
	home = getenv("HOME");
	if (command_line[1] != NULL && !ft_strcmp(command_line[1], "$HOME"))
	{
		chdir(home);
	}
	else if (!command_line[1])
	{
		chdir(home);
	}
	else if (chdir(command_line[1]))
		;
	//exit(0);
}
