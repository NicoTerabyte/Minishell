/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_behaviours.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:46:45 by lnicoter          #+#    #+#             */
/*   Updated: 2023/09/21 20:48:49 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_if_needed(t_data *shell_data, int pos)
{
	char			*support_str;

	support_str = NULL;
	if (shell_data->identity->value != NULL)
	{
		free(shell_data->export_env[pos]);
		shell_data->export_env[pos] = ft_strdup(shell_data->identity->name);
		shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], "=");
		if (!ft_strchr(shell_data->identity->value, '\"') && !ft_strchr(shell_data->identity->value, '\''))
		{
			shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], "\"");
			shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], shell_data->identity->value);
			shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], "\"");
		}
		else if (ft_strchr(shell_data->identity->value, '\''))
		{
			support_str = i_hate_this_strcpy_for_apix(support_str, shell_data->identity->value);
			shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], support_str);
			free(support_str);
		}
		else
			shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], shell_data->identity->value);
	}
	else if (shell_data->identity->concatenation != 0)
	{
		shell_data->export_env[pos] = ft_strdup(shell_data->identity->name);
		shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], "=");
		shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], "\"");
		shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], "\"");
	}
}

int		check_doubles(t_data *shell_data)
{
	int		i;
	int		word_len;

	word_len = ft_strlen(shell_data->identity->name);
	i = 0;

	while (shell_data->export_env[i])
	{
		//printf("ogni valore %s\n", shell_data->export_env[i]);
		if (ft_strncmp(shell_data->export_env[i], shell_data->identity->name, word_len) == 0)
		{
			printf("copia trovata \n");
			change_if_needed(shell_data, i);
			return (1);
		}
		i++;
	}
	return (0);
}
