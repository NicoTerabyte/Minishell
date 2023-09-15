/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_behaviours.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:46:45 by lnicoter          #+#    #+#             */
/*   Updated: 2023/09/15 18:40:05 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_if_needed(t_data *shell_data, t_declaration *identity, int pos)
{
	if (identity->value != NULL)
	{
		free(shell_data->copy_env[pos]);
		shell_data->copy_env[pos] = ft_strdup(identity->name);
		shell_data->copy_env[pos] = ft_strjoin(shell_data->copy_env[pos], "=");
		shell_data->copy_env[pos] = ft_strjoin(shell_data->copy_env[pos], "\"");
		shell_data->copy_env[pos] = ft_strjoin(shell_data->copy_env[pos], identity->value);
		shell_data->copy_env[pos] = ft_strjoin(shell_data->copy_env[pos], "\"");
	}
}

int		check_doubles(t_data *shell_data, t_declaration *identity)
{
	int		i;
	int		word_len;

	word_len = ft_strlen(identity->name);
	i = 0;

	while (shell_data->copy_env[i])
	{
		//printf("ogni valore %s\n", shell_data->copy_env[i]);
		if (ft_strncmp(shell_data->copy_env[i], identity->name, word_len) == 0)
		{
			printf("copia trovata \n");
			change_if_needed(shell_data, identity, i);
			return (1);
		}
		i++;
	}
	return (0);
}
