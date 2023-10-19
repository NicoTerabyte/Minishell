/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_adding_only_for_env.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:05:44 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/19 20:29:41 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
qua devi aggiustare per la sovrascrittura e poi
passa alla concatenazione
la versione alternativa di change_if_needed deve praticamente sistemare i valori
togliendo nel caso le " o gli '
*/
int	check_if_good_for_env(t_declaration *node) //teniamolo aiuta per rendere le variabili più facili da gestire
{
	char	*tmp;

	tmp = NULL;
	if (node->value != NULL && (ft_strchr(node->value, '\'')
		|| ft_strchr(node->value, '\"')))
	{
		tmp = ft_strndup(node->value, 1, ft_strlen(node->value));
		free(node->value);
		node->value = tmp; //logica puntatori
		return(0);
	}
	return (1);
}

void	add_to_the_real_env(t_declaration *node, char ***env)
{
	int	i;
	printf("export cheeeck n1\n");
	i = 0;
	while(env[i])
		i++;
	env = realloc(env, (i + 2) * sizeof(char *));
	env[i] = ft_strdup(node->name);
	env[i + 1] = 0;
	check_if_good_for_env(node);
	env[i] = ft_strjoin_damn_you_leaks(env[i], "=");
	if (node->value)
		env[i] = ft_strjoin_damn_you_leaks(env[i], node->value);
	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
	env_container(1, env);
}
