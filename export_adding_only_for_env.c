/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_adding_only_for_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:05:44 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/01 13:35:47 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
qua devi aggiustare per la sovrascrittura e poi
passa alla concatenazione
la versione alternativa di change_if_needed deve praticamente sistemare i valori
togliendo nel caso le " o gli '
*/
int	check_if_good_for_env(t_data *shell_data, int index)
{
	char	*tmp;

	tmp = NULL;
	if (shell_data->identity->value != NULL && (ft_strchr(shell_data->identity->value, '\'')
		|| ft_strchr(shell_data->identity->value, '\"')))
	{
		tmp = ft_strndup(shell_data->identity->value, 1, ft_strlen(shell_data->identity->value));
		free(shell_data->identity->value);
		shell_data->identity->value = tmp; //logica puntatori
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
	shell_data->copy_env = realloc(shell_data->copy_env, (i + 2) * sizeof(char *));
	shell_data->copy_env[i] = ft_strdup(shell_data->identity->name);
	shell_data->copy_env[i + 1] = 0;
	check_if_good_for_env(shell_data, i);
	shell_data->copy_env[i] = ft_strjoin_damn_you_leaks(shell_data->copy_env[i], "=");
	if (shell_data->identity->value)
		shell_data->copy_env[i] = ft_strjoin_damn_you_leaks(shell_data->copy_env[i], shell_data->identity->value);
}
