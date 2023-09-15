/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_more_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:30:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/09/15 19:00:24 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_declaration(t_declaration **list, int concatenation, const char *name, const char *value)
{
	t_declaration *new_declaration = malloc(sizeof(t_declaration));
	if (!new_declaration)
	{
		perror("Memory allocation failed");
		free(new_declaration);
		exit(EXIT_FAILURE);
	}
	new_declaration->concatenation = concatenation;
	new_declaration->name = ft_strdup(name);
	if (value)
		new_declaration->value = ft_strdup(value);
	else
		new_declaration->value = NULL;
	new_declaration->next = *list;
	if (!*list)
		*list = new_declaration;
	// free(new_declaration->name);
	// free(new_declaration->value);
	// puppamelo(new_declaration);
}

//in realtà questo mi serve a simulare la cosa che fa manu
int	check_arguments_validation(char *identity_name_only)
{
	int	i;

	i = 0;
	if (!ft_isalpha(identity_name_only[0]))
	{
		printf("\033[1;31mbash: export: `%s': not a valid identifier\n", identity_name_only);
		return (0);
	}
	while (identity_name_only[i])
	{
		if (!ft_isalnum(identity_name_only[i]) && identity_name_only[i]!= '=' && identity_name_only[i] != '+')
		{
			printf("\033[1;31mbash: export: `%s': not a valid identifier\n", identity_name_only);
			return (0);
		}
		i++;
	}
	return (1);
}

void	print_list(t_declaration *list)
{
	while (list != NULL)
	{
		printf("name %s, conc %d, value %s\n", list->name, list->concatenation, list->value);
		list = list->next;
	}
}

void	arguments_separation(char **command_line, int conc, t_declaration **identity)
{
	char	**separated_args;
	int		plus_finder;
	int		i;

	plus_finder = 0;
	i = 0;
	while(command_line[++i])
	{
		separated_args = ft_split(command_line[i], '=');
		if (ft_strchr(separated_args[0], '+'))
		{
			conc = 1;
			while(separated_args[0][plus_finder])
			{
				if (separated_args[0][plus_finder] == '+')
					separated_args[0][plus_finder] = '\0';
				plus_finder++;
			}
		}
		insert_declaration(identity, conc, separated_args[0], separated_args[1]);
	}
	free_matrix(separated_args);
}
