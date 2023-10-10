/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overwrite_procedure.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 19:44:10 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/09 19:57:00 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	overwrite(t_data *shell_data, int pos)
{
	char	*support_str;

	support_str = NULL;
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
