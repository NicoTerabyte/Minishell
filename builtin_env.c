/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:11:25 by lnicoter          #+#    #+#             */
/*   Updated: 2023/08/06 19:57:39 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_data *shell_data, char **env)
{
	int		i;

	copy_env(env, shell_data);
	i = 0;
	while (shell_data->copy_env[i])
	{
		printf("%s\n", shell_data->copy_env[i]);
		i++;
	}
}

