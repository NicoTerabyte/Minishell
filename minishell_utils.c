/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:46:34 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/01 20:37:29 by lnicoter         ###   ########.fr       */
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
	mini_data->export_env = (char **)malloc((env_size + 1) * sizeof(char *));
	mini_data->copy_env = (char **)malloc((env_size + 1) * sizeof(char *));
	if (!mini_data->copy_env)
	{
		printf("Incombenza rilevata!!!\n");
		return (0); // Non c'è bisogno di liberare la memoria qui
	}
	while (i < env_size)
	{
		mini_data->copy_env[i] = env[i];
		mini_data->export_env[i] = env[i];
		i++;
	}
	mini_data->copy_env[i] = NULL;
	mini_data->export_env[i] = NULL;
	return (1);
}

void *ft_realloc(void *ptr, size_t size)
{
	void *new_ptr;

	// if (ptr)
	// {
	// 	if (size)
	// 	{
	// 		new_ptr = malloc(size);
	// 		if (!new_ptr)
	// 			return (NULL);
	// 		ft_bzero(new_ptr, size);
	// 		ft_memcpy(new_ptr, ptr, size);
	// 	}
	// 	else
	// 	{
	// 		new_ptr = (unsigned char *)malloc(sizeof(ptr));
	// 		if (!new_ptr)
	// 			return (NULL);
	// 	}
	// 	free(ptr);
	// 	return (new_ptr);
	// }
	if (!ptr)
		return (malloc(size));
	new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, size);
	free(ptr);
	return (new_ptr);
}

int	env_rows(t_data *shell_data)
{
	int	size;

	size = 0;
	while (shell_data->export_env[size])
		size++;
	return (size);
}

void	init_structs(t_data **shell_data, char **envp)
{

	//*identity = (t_declaration *)malloc(sizeof(t_declaration));
	*shell_data = (t_data *)malloc(sizeof(t_data));
	if (!*shell_data)
	{
		//free(identity);
		free(*shell_data);
		exit(0);
	}
	if(!copy_env(envp, *shell_data))
	{
		free(*shell_data);
		exit(0);
	}
}

void	puppamelo(t_data *lnico)
{
	t_declaration	*tmp;
	int				i;

	i = 0;
	while (lnico->identity)
	{
		print_list(lnico->identity);
		tmp = lnico->identity;
		lnico->identity = lnico->identity->next;
		free(tmp->name);
		i++;
		if (tmp->value)
			free(tmp->value); //invalid free stranamente
		free(tmp);
	}
	printf("si stat liberat\n");
}
