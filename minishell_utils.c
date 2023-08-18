/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:46:34 by lnicoter          #+#    #+#             */
/*   Updated: 2023/08/17 17:56:24 by lnicoter         ###   ########.fr       */
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
	mini_data->copy_env = (char **)malloc(env_size * sizeof(char *) + 1);
	if (!mini_data->copy_env)
	{
		free(mini_data->copy_env);
		return (0);
	}
	while (env[i])
	{
		mini_data->copy_env[i] = env[i];
		i++;
	}
	mini_data->copy_env[i] = env[i];
	i++;
	mini_data->copy_env[i] = 0;
	return (1);
}

void *ft_realloc(void *ptr, size_t size)
{
	void *new_ptr;

	if (ptr)
	{
		if (size)
		{
			new_ptr = malloc(size);
			if (!new_ptr)
				return (NULL);
			ft_bzero(new_ptr, size);
			ft_memcpy(new_ptr, ptr, size);
		}
		else
		{
			new_ptr = (unsigned char *)malloc(sizeof(ptr));
			if (!new_ptr)
				return (NULL);
		}
		free(ptr);
		return (new_ptr);
	}
	return ((unsigned char *)malloc(sizeof(ptr) * size));
}

int	env_rows(t_data *shell_data)
{
	int	size;

	size = 0;
	while (shell_data->copy_env[size])
		size++;
	return (size);
}
