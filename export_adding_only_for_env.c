/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_adding_only_for_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:05:44 by lnicoter          #+#    #+#             */
/*   Updated: 2023/09/19 18:55:51 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_good_for_env(t_data *shell_data, t_declaration *identity, int index)
{
	int	i;
	int	j;
	// int	len;

	// len = ft_strlen(identity->value);
	// i = 0;
	shell_data->copy_env[index] = ft_strjoin_damn_you_leaks(shell_data->copy_env[index], "=");
	if ( identity->value != NULL && (ft_strchr(identity->value, '\'')
		|| ft_strchr(identity->value, '\"')))
	{
		shell_data->copy_env[index] = ft_strjoin_damn_you_leaks(shell_data->copy_env[index], identity->value);
		i = ft_strlen(shell_data->copy_env[index]);
		while (identity->value[j])
		{
			if (identity->value[j])
		}
		return(0);
	}
	return (1);
}

void	add_to_the_real_env(t_data *shell_data, t_declaration *identity)
{
	int	i;

	i = 0;
	while(shell_data->copy_env[i])
		i++;
	shell_data->copy_env = realloc(shell_data->copy_env, (i + 1) * sizeof(char *));
	shell_data->copy_env[i - 1] = ft_strdup(identity->name);
	shell_data->copy_env[i] = 0;
	if (check_if_good_for_env(shell_data, identity, i - 1) != 0)
	{
		shell_data->copy_env[i - 1] = ft_strjoin_damn_you_leaks(shell_data->copy_env[i - 1], "=");
		shell_data->copy_env[i - 1] = ft_strjoin_damn_you_leaks(shell_data->copy_env[i - 1], identity->value);
	}
}
