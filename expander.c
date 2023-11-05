/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/05 19:31:14 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_logic_norm(char *input, char quote, t_data *shell_data)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == quote)
		{
			i++;
			break ;
		}
		else if (input[i] == '$' && quote == '"')
			shell_data->ret_exp = manage_dollar_norm(input, &i, shell_data->ret_exp, shell_data);
		else
			ft_strncat(shell_data, input[i++], 1);
	}
	return (i);
}

char	*expander(t_data *shell_data, char *input)
{
	int		i;
	char	quote;

	i = 0;
	shell_data->ret_exp = ft_calloc(1, sizeof(char));
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			shell_data->ret_exp = manage_dollar_norm(input, &i, shell_data->ret_exp, shell_data);
		else if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			i += quote_logic_norm(&input[i], quote, shell_data);
		}
		else
			ft_strncat(shell_data, input[i++], 1);
	}
	if (shell_data->ret_exp && ft_strlen(shell_data->ret_exp) <= 3 && ft_strchr(shell_data->ret_exp, '\''))
		shell_data->ret_exp = handle_apix_case(shell_data->ret_exp);
	return (shell_data->ret_exp);
}
