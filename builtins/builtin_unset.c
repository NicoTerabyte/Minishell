/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:16:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/13 19:10:48 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//funzione che cerca il valore da cambiare
//funzione ch ecambia il valore che stai cercando
//dopo aver scalato la matrice mettere il NULL byte
//per sistemare l'unset, come? scalando la matrice
//e tenendo conto di quanto è grande l'array mettere
//in size - 1 il null byte cosicché aggiorni bene
//l'env
void	fix_mat(char **env, int i)
{
	while (env[i + 1])
	{
		swap_mat(&env[i], &env[i + 1]);
		//swap_mat(&shell_data->export_env[i], &shell_data->export_env[i + 1]); export version da fare
		i++;
	}
	env[i] = 0;
	//shell_data->export_env[i] = 0;
}

void	copy_check_unset(char *str)
{
	int		i;
	int		j;
	char	**env;

	env = env_container(7, env);
	i = -1;
	while (env[++i])
	{
		j = -1;
		while (env[i][++j] == '=' && env[i][j])
			;
		if (ft_strncmp(env[i], str, j) == 0)
		{
			if (ft_strncmp(env[i], str,
				ft_strlen(str)) == 0)
			{
				free(env[i]);
				//free(shell_data->export_env[pos]); export version
				break ;
			}
		}
	}
	fix_mat(env, i);
}

void	ft_unset(t_declaration *node)
{
	int	i;

	i = 0;
	if (!node)
		return ;
	while (node)
	{
		copy_check_unset(node->name);
		node = node->next;
	}
}

