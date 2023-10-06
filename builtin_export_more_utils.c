/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_more_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 20:30:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/04 00:43:50 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	insert_declaration(t_data *shell_data, int concatenation, const char *name, const char *value)
{
	if (shell_data->identity == NULL)
	{
		shell_data->identity = ft_calloc(1, sizeof(t_declaration));
	}
	else
	{
		shell_data->identity->next = ft_calloc(1, sizeof(t_declaration));
		shell_data->identity = shell_data->identity->next;
	}
	shell_data->identity->concatenation = concatenation;
	shell_data->identity->name = ft_strdup(name);
	if (value)
		shell_data->identity->value = ft_strdup(value);
	shell_data->identity->next = NULL;
	if (!shell_data->head)
	{
		printf("checkout bro...\n");
		shell_data->head = shell_data->identity;
	}
	printf("CHECK PER IL SECONDO GIRO DELLA LISTA\n");
	print_list(shell_data->head);
	printf("FINE CONTROLLO PER IL SECONDO GIRO\n");
}

//in realtà questo mi serve a simulare la cosa che fa manu
int	check_arguments_validation(char *identity_name_only)
{
	int	i;

	i = 0;
	if (!ft_isalpha(identity_name_only[0]))
	{
		printf("\033[1;31mbash: export: `%s': not a valid identifier\n\033\e[0m", identity_name_only);
		return (0);
	}
	while (identity_name_only[i])
	{
		if (!ft_isalnum(identity_name_only[i]) && identity_name_only[i]!= '=' && identity_name_only[i] != '+')
		{
			printf("\033[31mbash: export: `%s': not a valid identifier\n\e[0m", identity_name_only);
			return (0);
		}
		else if (identity_name_only[i] == '=')
		{
			printf("tutto ok\n");
			return (1);
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

void	arguments_separation(t_data *shell_data, char **command_line, int conc)
{
	char	**separated_args;
	int		plus_finder;
	int		i;

	plus_finder = 0;
	i = 0;
	while(command_line[++i])
	{
		if (check_arguments_validation(command_line[i]))
		{
			if (ft_strchr(command_line[i], '='))
				conc = 1;
			separated_args = split_bt_nt_t_mc(command_line[i], '='); // ciao,    comeva=ds
			printf("check arguments %s\n value %s\n",separated_args[0], separated_args[1]);
			if (ft_strchr(separated_args[0], '+'))
			{
				conc = 2;
				while(separated_args[0][plus_finder])
				{
					if (separated_args[0][plus_finder] == '+')
						separated_args[0][plus_finder] = '\0';
					plus_finder++;
				}
			}
			insert_declaration(shell_data, conc, separated_args[0], separated_args[1]);
			conc = 0;
		}
	}
	shell_data->identity = shell_data->head;
	free_matrix(separated_args);
}
