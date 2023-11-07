/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:46:34 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/07 15:22:29 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	copy_env(char **env, t_mini *all)
{
	int	env_size;
	int	i;

	env_size = 0;
	i = 0;
	while (env[env_size])
		env_size++;
	all->env = ft_calloc((env_size + 1), sizeof(char *));
	if (!all->env)
	{
		printf("Incombenza rilevata!!!\n");
		return (0); // Non c'è bisogno di liberare la memoria qui
	}
	while (env[i])
	{
		all->env[i] = ft_strdup(env[i]);
		i++;
	}
	all->env[i] = 0;
	return (1);
}

int	env_rows(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

//export x unset 
