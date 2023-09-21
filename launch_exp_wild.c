/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exp_wild.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:57:02 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/21 21:10:31 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int only_star(char *str)
{
	int i;
	if (str == NULL)
		return 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '*')
			return 0;
		i++;
	}

	return 1;
}

char *launch_exp_wild(t_data *shell_data, char *input)
{
	char *ret;
	int i;

	i = 0;
	ret = translate_exp(shell_data, input);
	if (is_wildcard(input))
	{
		shell_data->file = matrix_file(shell_data);
		if (only_star(input) == 1)
		{
			ret = ft_strdup("");
			while (shell_data->file[i] != NULL)
			{
			ret = ft_strjoin_wild(ret, shell_data->file[i]->d_name);
			i++;
			}
			return ret;
		}
		ret = translate_wild(shell_data, input);
	}
	return (ret);
}
