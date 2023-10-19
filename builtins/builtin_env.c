/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 16:11:25 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/12 15:55:15 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_env(void)
{
	int		i;
	char	**env;

	env = env_container(7, env);
	i = 0;
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}

