/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_more_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:30:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/28 18:30:29 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

// void	insert_declaration(t_data *shell_data, int concatenation, const char *name, const char *value)
// {
// 	if (shell_data->identity == NULL)
// 	{
// 		shell_data->identity = ft_calloc(1, sizeof(t_declaration));
// 	}
// 	else
// 	{
// 		shell_data->identity->next = ft_calloc(1, sizeof(t_declaration));
// 		shell_data->identity = shell_data->identity->next;
// 	}
// 	shell_data->identity->concatenation = concatenation;
// 	shell_data->identity->name = ft_strdup(name);
// 	if (value)
// 		shell_data->identity->value = ft_strdup(value);
// 	shell_data->identity->next = NULL;
// 	if (!shell_data->head)
// 		shell_data->head = shell_data->identity;

// }

//in realtà questo mi serve a simulare la cosa che fa manu
int	check_arguments_validation(char *identity_name_only)
{
	int	i;

	i = 0;
	if (!ft_isalpha(identity_name_only[0]))
	{
		printf("\033[1;31mbash: export: `%s': not a valid identifier\n\033\e[0m", identity_name_only);
		last_exit_status_cmd = 1;
		return (0);
	}
	while (identity_name_only[i])
	{
		if (!ft_isalnum(identity_name_only[i]) && identity_name_only[i]!= '=' && identity_name_only[i] != '+')
		{
			printf("\033[31mbash: export: `%s': not a valid identifier\n\e[0m", identity_name_only);
			last_exit_status_cmd = 1;
			return (0);
		}
		else if (identity_name_only[i] == '=')
			return (1);
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

// void	arguments_separation(t_data *shell_data, char **command_line, int conc)
// {
// 	int		i;

// 	i = 0;
// 	while(command_line[++i])
// 		list_update(shell_data, conc, command_line, i);
// 	shell_data->identity = shell_data->head;
// }
