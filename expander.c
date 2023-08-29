/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/08/29 16:55:05 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp_env(const char *input, const char *env)
{
	while (*env != '=')
	{
		if (*input != *env)
		{
			return 1;
		}
		input++;
		env++;
	}
	return 0;
}

char *find_in_env(t_data *shell_data, char *input)
{
	int i = 0;
	int x = 0;
	char *ret = malloc(strlen(input) + 1);
	char *value_start;
	char *var;
	if (ret == NULL)
	{
		fprintf(stderr, "Errore nell'allocazione di memoria\n");
		return NULL;
	}
	while (*input)
	{
		if (*input == '$' && *(input + 1) && ft_isalpha(*(input + 1)))
		{
			input++;
			while(ft_isalnum(*(input)) && *input == '_')
				*(var++) = *(input++);
			while (shell_data->copy_env[i])
			{
				if (ft_strcmp_env(var, shell_data->copy_env[i]) == 0)
				{
					char *value_start = ft_strchr(shell_data->copy_env[i], '=') + 1;
					strcat(ret, value_start);
					break;
				}
				i++;
			}
		}
		else
			ret[x++] = *(input++);
	}
	return ret;
}
