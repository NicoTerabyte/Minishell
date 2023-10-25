/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_behaviours.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 15:46:45 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/25 18:06:11 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	concatenation_export(t_declaration *node, int pos, t_mini *mini)
{
	char	*tmp_value;
	if (ft_strchr(mini->env[pos], '='))
		tmp_value = ft_strndup(mini->env[pos], 0, ft_strlen(mini->env[pos]));
	else
		tmp_value = ft_strdup(mini->env[pos]);
	printf("CONTROLLO TMP VALUE %s\n", tmp_value);
	free(mini->env[pos]);
	mini->env[pos] = tmp_value;
	if (!ft_strchr(mini->env[pos], '='))
	{
		mini->env[pos] = ft_strjoin(node->name, "=");
		// mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], "=");
		// mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], "\"");
	}
	mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], node->value);
	// mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], "\"");
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
// 		all->env[pos] = ft_strdup(node->name);
// 		all->env[pos] = ft_strjoin_damn_you_leaks(all->env[pos], "=");
// 		all->env[pos] = ft_strjoin_damn_you_leaks(all->env[pos], "\"");
// 		all->env[pos] = ft_strjoin_damn_you_leaks(all->env[pos], "\"");
// 	}
// }

void	change_if_needed_env_ver(t_declaration *node, int pos, t_mini *mini)
{
	if (node->value != NULL)
	{
		free(mini->env[pos]);
		mini->env[pos] = ft_strdup(node->name);
		check_if_good_for_env(node);
		mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], "=");
		mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], node->value);
	}
	else if (node->concatenation == 1)
	{
		free(mini->env[pos]);
		mini->env[pos] = ft_strdup(node->name);
		mini->env[pos] = ft_strjoin_damn_you_leaks(mini->env[pos], "=");
	}
}
/*per ora gestisce solo il caso export bisogna
fare la chiamata di una funzione a parte per gestire anche i doppioni in env
ancora da sistemare inserita nell'env con = e la roba dei doppioni daje lo famo sta sera
me la sento
fare un change_if_needed per l'env dove devo gestire diversi casi
Se non c'è value non applichi nessun cambiamento */
int		check_doubles(t_declaration *node, t_mini *mini)
{
	int		i;
	int		word_len;

	word_len = ft_strlen(node->name);
	i = 0;

	while (mini->env[i]) //env
	{
		if (ft_strncmp(mini->env[i], node->name, word_len) == 0
			&& (node->concatenation == 1 || node->concatenation == 0))
		{
			change_if_needed_env_ver(node, i, mini);
			return (1);
		}
		if (ft_strncmp(mini->env[i], node->name, word_len) == 0
				&& node->concatenation == 2)
		{
			concatenation_export(node, i, mini);
			return (1);
		}
		i++;
	}
	return (0);
}
