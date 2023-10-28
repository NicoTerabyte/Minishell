/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 20:16:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/28 18:25:54 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

//funzione che cerca il valore da cambiare
//funzione ch ecambia il valore che stai cercando
//dopo aver scalato la matrice mettere il NULL byte
//per sistemare l'unset, come? scalando la matrice
//e tenendo conto di quanto è grande l'array mettere
//in size - 1 il null byte cosicché aggiorni bene
//l'all->env
void	fix_mat(t_mini *mini, int i)
{
	while (mini->env[i + 1])
	{
		swap_mat(&mini->env[i], &mini->env[i + 1]);
		//swap_mat(&shell_data->export_mini->env[i], &shell_data->export_mini->env[i + 1]); export version da fare
		i++;
	}
	mini->env[i] = 0;
	//shell_data->export_mini->env[i] = 0;
}

void	copy_check_unset(char *str, t_mini *mini)
{
	int		i;
	int		j;

	i = -1;
	while (mini->env[++i])
	{
		j = -1;
		while (mini->env[i][++j] == '=' && mini->env[i][j])
			;
		if (ft_strncmp(mini->env[i], str, j) == 0)
		{
			if (ft_strncmp(mini->env[i], str,
				ft_strlen(str)) == 0)
			{
				free(mini->env[i]);
				//free(shell_data->export_all->env[pos]); export version
				break ;
			}
		}
	}
	fix_mat(mini, i);
}

int		ft_unset(t_declaration *node, t_mini *mini)
{
	int	i;

	i = 0;
	if (!node)
		return (0);
	while (node)
	{
		copy_check_unset(node->name, mini);
		node = node->next;
	}
	return (0);
}

