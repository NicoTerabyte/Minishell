/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_adding_only_for_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:05:44 by lnicoter          #+#    #+#             */
/*   Updated: 2023/09/22 15:16:01 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_good_for_env(t_data *shell_data, int index)
{
	int	i;
	int	j;

	if (shell_data->identity->value != NULL && (ft_strchr(shell_data->identity->value, '\'')
		|| ft_strchr(shell_data->identity->value, '\"')))
	{
		shell_data->identity->value = &shell_data->identity->value[1]; //logica puntatori
		shell_data->identity->value[ft_strlen(shell_data->identity->value) - 1] = '\0';
		return(0);
	}
	return (1);
}

void	add_to_the_real_env(t_data *shell_data)
{
	int	i;

	i = 0;
	while(shell_data->copy_env[i])
		i++;
	shell_data->copy_env = realloc(shell_data->copy_env, (i + 1) * sizeof(char *));
	shell_data->copy_env[i - 1] = ft_strdup(shell_data->identity->name);
	shell_data->copy_env[i] = 0;
	check_if_good_for_env(shell_data, i - 1);
	shell_data->copy_env[i - 1] = ft_strjoin_damn_you_leaks(shell_data->copy_env[i - 1], "=");
	shell_data->copy_env[i - 1] = ft_strjoin_damn_you_leaks(shell_data->copy_env[i - 1], shell_data->identity->value);

}
