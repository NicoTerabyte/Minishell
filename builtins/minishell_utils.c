/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:46:34 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/31 11:14:27 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
	la copy_env va cambiata rispettivamente per gestire come si deve
	la copiatura dell'environment, i dubbi che mi vengono sono due però
	1)come cambio in maniera permanente un valore per far sì che
		non dia problemi? (perché lo sto passando con un cast magari se faccio
		un cast triplo (char ***) si risolve)
	2) posso cambiare la funzione in modo tale che il valore passato
		venga ritornato alla fine senza dovermi fare troppe pippe con il triplo
		cast?
	in ogni
*/
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

void *ft_realloc(void *ptr, size_t size)
{
	void *new_ptr;

	new_ptr = NULL;
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
	return (new_ptr);
}

int	env_rows(char **env)
{
	int	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

//da eliminare mi sa
/*void	init_structs(t_data **shell_data, char **envp)
{
	*shell_data = (t_data *)malloc(sizeof(t_data));
	if (!*shell_data)
	{
		free(*shell_data);
		exit(0);
	}
	if(!copy_env(envp, *shell_data))
	{
		free(*shell_data);
		exit(0);
	}
	(*shell_data)->identity = NULL;
	(*shell_data)->head = NULL;
	(*shell_data)->path = NULL;
	(*shell_data)->old_path = NULL;
}*/

// void	puppamelo(t_data *lnico)
// {
// 	t_declaration	*tmp;
// 	int				i;

// 	i = 0;
// 	while (lnico->identity)
// 	{
// 		tmp = lnico->identity;
// 		lnico->identity = lnico->identity->next;
// 		free(tmp->name);
// 		i++;
// 		if (tmp->value)
// 			free(tmp->value);
// 		tmp->concatenation = 0;
// 		free(tmp);
// 	}
// 	if (lnico->identity)
// 		printf("qualcosa e' andato male liberazione della memoria fatta a buffo\n");
// 	else
// 		printf("tutto ok liberato in maniera corretta\n");
// 	lnico->head = NULL;
// }
