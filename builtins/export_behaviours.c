/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_behaviours.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:46:45 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/18 19:55:40 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	concatenation_export(t_declaration *node, int pos, char **env)
{
	char	*tmp_value;
	if (ft_strchr(env[pos], '='))
		tmp_value = ft_strndup(env[pos], 0, ft_strlen(env[pos]) - 1);
	else
		tmp_value = ft_strdup(env[pos]);
	printf("CONTROLLO TMP VALUE %s\n", tmp_value);
	free(env[pos]);
	env[pos] = tmp_value;
	if (!ft_strchr(env[pos], '='))
	{
		env[pos] = ft_strjoin_damn_you_leaks(env[pos], "=");
		env[pos] = ft_strjoin_damn_you_leaks(env[pos], "\"");
		env[pos] = ft_strjoin(node->name, "=");
	}
	env[pos] = ft_strjoin_damn_you_leaks(env[pos], node->value);
	env[pos] = ft_strjoin_damn_you_leaks(env[pos], "\"");
	env[pos] = ft_strjoin_damn_you_leaks(env[pos], node->value);
}

//questa parte è molto problabile che venga esclusa perché le stampe sono state corrette
//in modo tale che sia env che export stampino i propri valori senza problemi (da fixare env hai perso i dati)
//
// void	change_if_needed(t_declaration *node, int pos)
// {
// 	if (node->value != NULL)
// 		overwrite(shell_data, pos);
// 	else if (node->concatenation != 0)
// 	{
// 		env[pos] = ft_strdup(node->name);
// 		env[pos] = ft_strjoin_damn_you_leaks(env[pos], "=");
// 		env[pos] = ft_strjoin_damn_you_leaks(env[pos], "\"");
// 		env[pos] = ft_strjoin_damn_you_leaks(env[pos], "\"");
// 	}
// }

void	change_if_needed_env_ver(t_declaration *node, int pos, char **env)
{
	if (node->value != NULL)
	{
		free(env[pos]);
		env[pos] = ft_strdup(node->name);
		check_if_good_for_env(node);
		env[pos] = ft_strjoin_damn_you_leaks(env[pos], "=");
		env[pos] = ft_strjoin_damn_you_leaks(env[pos], node->value);
	}
	else if (node->concatenation == 1)
	{
		free(env[pos]);
		env[pos] = ft_strdup(node->name);
		env[pos] = ft_strjoin_damn_you_leaks(env[pos], "=");
	}
}
/*per ora gestisce solo il caso export bisogna
fare la chiamata di una funzione a parte per gestire anche i doppioni in env
ancora da sistemare inserita nell'env con = e la roba dei doppioni daje lo famo sta sera
me la sento
fare un change_if_needed per l'env dove devo gestire diversi casi
Se non c'è value non applichi nessun cambiamento */
int		check_doubles(t_declaration *node, char **env)
{
	int		i;
	int		word_len;

	word_len = ft_strlen(node->name);
	i = 0;

	while (env[i]) //env
	{
		if (ft_strncmp(env[i], node->name, word_len) == 0
			&& (node->concatenation == 1 || node->concatenation == 0))
		{
			//change_if_needed(shell_data, i);
			change_if_needed_env_ver(node, i, env);
			return (1);
		}
		if (ft_strncmp(env[i], node->name, word_len) == 0
				&& node->concatenation == 2)
		{
			concatenation_export(node, i, env);
			return (1);
		}
		i++;
	}
	return (0);
}
