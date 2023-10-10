/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:16:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/06 17:59:27 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//funzione che cerca il valore da cambiare
//funzione ch ecambia il valore che stai cercando
//dopo aver scalato la matrice mettere il NULL byte
//per sistemare l'unset, come? scalando la matrice
//e tenendo conto di quanto è grande l'array mettere
//in size - 1 il null byte cosicché aggiorni bene
//l'env
void	fix_mat(t_data *shell_data, int i)
{
	while (shell_data->copy_env[i + 1])
	{
		swap_mat(&shell_data->copy_env[i], &shell_data->copy_env[i + 1]);
		swap_mat(&shell_data->export_env[i], &shell_data->export_env[i + 1]);
		i++;
	}
	shell_data->copy_env[i] = 0;
	shell_data->export_env[i] = 0;
}

void	copy_check_unset(t_data *shell_data, char **command_line, int pos)
{
	int	i;
	int	j;

	i = -1;
	while (shell_data->copy_env[++i])
	{
		j = -1;
		while (shell_data->copy_env[i][++j] == '=' && shell_data->copy_env[i][j])
			;
		if (ft_strncmp(shell_data->copy_env[i], command_line[pos], j) == 0)
		{
			if (ft_strncmp(shell_data->copy_env[i], command_line[pos],
				ft_strlen(command_line[pos])) == 0)
			{
				free(shell_data->copy_env[pos]);
				free(shell_data->export_env[pos]);
				break ;
			}
		}
	}
	fix_mat(shell_data, i);
}

void	ft_unset(t_data *shell_data, char **command_line)
{
	int	i;

	i = 0;
	if (!command_line[1])
		return ;
	while (command_line[++i])
	{
		copy_check_unset(shell_data, command_line, i);
	}
	printf("chiudiamo baracca qua\n");
}
