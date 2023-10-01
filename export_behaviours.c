/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_behaviours.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:46:45 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/01 13:04:33 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
aggiunta della funzione per la concatenazione verrà evocata se c'è un duplicato
Sviluppo delle casistiche
*/
void	concatenation_export(t_data *shell_data, int pos)
{
	char	*tmp_value;
	//prima di fare questa operazione devi trovare il modo di liberare
	//la stringa perché essa viene mallocata precedentemente con malloc prima
	//fai na versione che libera prima di creare un duplicato di strdup
	tmp_value = ft_strndup(shell_data->export_env[pos], 0, ft_strlen(shell_data->export_env[pos]) - 1);
	free(shell_data->export_env[pos]);
	shell_data->export_env[pos] = tmp_value;
	shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], shell_data->identity->value);
	shell_data->export_env[pos] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos], "\"");
	printf("copienv prima dell'aggiornamento %s\n", shell_data->copy_env[pos]); //non c'è assolutamente NULLA
	shell_data->copy_env[pos] = ft_strjoin_damn_you_leaks(shell_data->copy_env[pos], shell_data->identity->value);
}

void	change_if_needed(t_data *shell_data, int pos)
{
	char			*support_str;

	support_str = NULL;
	if (shell_data->identity->value != NULL)
	{
		free(shell_data->export_env[pos - 1]);
		shell_data->export_env[pos - 1] = ft_strdup(shell_data->identity->name);
		shell_data->export_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos - 1], "=");
		if (!ft_strchr(shell_data->identity->value, '\"') && !ft_strchr(shell_data->identity->value, '\''))
		{
			shell_data->export_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos - 1], "\"");
			shell_data->export_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos - 1], shell_data->identity->value);
			shell_data->export_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos - 1], "\"");
		}
		else if (ft_strchr(shell_data->identity->value, '\''))
		{
			support_str = i_hate_this_strcpy_for_apix(support_str, shell_data->identity->value);
			shell_data->export_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos - 1], support_str);
			free(support_str);
		}
		else
			shell_data->export_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos - 1], shell_data->identity->value);
	}
	else if (shell_data->identity->concatenation != 0)
	{
		shell_data->export_env[pos - 1] = ft_strdup(shell_data->identity->name);
		shell_data->export_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos - 1], "=");
		shell_data->export_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos - 1], "\"");
		shell_data->export_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->export_env[pos - 1], "\"");
	}
}

void	change_if_needed_env_ver(t_data	*shell_data, int pos)
{
	if (shell_data->identity->value != NULL)
	{
		free(shell_data->copy_env[pos - 1]);
		shell_data->copy_env[pos - 1] = ft_strdup(shell_data->identity->name);
		check_if_good_for_env(shell_data, pos - 1);
		shell_data->copy_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->copy_env[pos - 1], "=");
		shell_data->copy_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->copy_env[pos - 1], shell_data->identity->value);
	}
	else if (shell_data->identity->concatenation == 1)
	{
		free(shell_data->copy_env[pos]);
		shell_data->copy_env[pos - 1] = ft_strdup(shell_data->identity->name);
		shell_data->copy_env[pos - 1] = ft_strjoin_damn_you_leaks(shell_data->copy_env[pos - 1], "=");
	}
}
/*per ora gestisce solo il caso export bisogna
fare la chiamata di una funzione a parte per gestire anche i doppioni in env
ancora da sistemare inserita nell'env con = e la roba dei doppioni daje lo famo sta sera
me la sento
fare un change_if_needed per l'env dove devo gestire diversi casi
Se non c'è value non applichi nessun cambiamento */
int		check_doubles(t_data *shell_data)
{
	int		i;
	int		word_len;

	word_len = ft_strlen(shell_data->identity->name);
	i = 0;

	while (shell_data->export_env[i])
	{
		if (ft_strncmp(shell_data->export_env[i], shell_data->identity->name, word_len) == 0
			&& shell_data->identity->concatenation == 1)
		{
			printf("copia trovata \n");
			change_if_needed(shell_data, i);
			change_if_needed_env_ver(shell_data, i);
			return (1);
		}
		if (ft_strncmp(shell_data->export_env[i], shell_data->identity->name, word_len) == 0
				&& shell_data->identity->concatenation == 2)
		{
			concatenation_export(shell_data, i);
			return (1);
		}
		i++;
	}
	return (0);
}
