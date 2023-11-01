/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:46:34 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/01 17:54:26 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	copy_env(char **env, t_data *mini_data)
{
	int	env_size;
	int	i;

	env_size = 0;
	i = 0;
	while (env[env_size])
		env_size++;

	// Allocazione di spazio per env_size + 1 puntatori
	mini_data->copy_env = (char **)malloc((env_size + 1) * sizeof(char *));
	if (!mini_data->copy_env)
	{
		printf("Incombenza rilevata!!!\n");
		return (0); // Non c'è bisogno di liberare la memoria qui
	}

	while (i < env_size)
	{
		mini_data->copy_env[i] = ft_strdup(env[i]);
		i++;
	}
	mini_data->copy_env[i] = NULL; // Imposta l'ultimo puntatore a NULL

	return (1);
}

void	*ft_realloc(void *p, size_t size, int dim, int new_dim)
{
	char		*new_p;
	size_t		i;

	new_p = (char *)malloc(size * new_dim);
	if (!new_p)
		return (NULL);
	i = 0;
	while (i < size * new_dim)
	{
		if (i < size * dim)
			new_p[i] = ((char *) p)[i];
		else
			new_p[i] = 0;
		i++;
	}
	free(p);
	return ((void *) new_p);
}


int	env_rows(t_data *shell_data)
{
	int	size;

	size = 0;
	while (shell_data->copy_env[size])
		size++;
	return (size);
}
