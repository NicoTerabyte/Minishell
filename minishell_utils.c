/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:46:34 by lnicoter          #+#    #+#             */
/*   Updated: 2023/08/06 19:18:24 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//modificare la funzione in modo tale che
//char **copy aggiorni la struct dei dati
void	copy_env(char **env, t_data *mini_data)
{
	int	env_size;
	int	i;

	env_size = 0;
	i = 0;
	while (env[env_size])
		env_size++;
	mini_data->copy_env = malloc(env_size * sizeof(char *));
	while (env[i])
	{
		mini_data->copy_env[i] = env[i];
		i++;
	}
	mini_data->copy_env[i] = env[i];
}

void	update_path(t_data *mini_data) //update del path in modo globale
{
	printf("il nulla\n");
}
