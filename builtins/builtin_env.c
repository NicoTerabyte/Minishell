/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:11:25 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/10 22:44:59 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(t_data *shell_data)
{
	int		i;

	i = 0;
	while (shell_data->copy_env[i])
	{
		printf("%s\n", shell_data->copy_env[i]);
		i++;
	}
}

