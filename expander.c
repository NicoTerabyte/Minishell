/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/03 14:50:14 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_logic_norm(char *input, char **ret, char quote, t_data *shell_data)
{
	int	i;

	printf("new input %c\n", input[i]);
	i = 0;
	while (input[i] != '\0')
	{
		printf("i value %d\n", i);
		if (input[i] == quote)
		{
			i++;
			break ;
		}
		else if (input[i] == '$' && quote == '"')
		{
			printf("Qui entra\n");
			*ret = manage_dollar_norm(input, &i, *ret, shell_data);
		}
		else
		{
			ft_strncat(ret, input[i++], 1); //con "'$us'" va qui ret = '\0'
			printf("ret value after cat %s\n", *ret);
		}
	}
	printf("ret dopo logica %s\n", *ret);
	return (i);
}

char	*expander(t_data *shell_data, char *input)
{
	char	*ret;
	int		i;
	char	quote;

	i = 0;
	ret = ft_strdup("");
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			ret = manage_dollar_norm(input, &i, ret, shell_data);
		else if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			i += quote_logic_norm(&input[i], &ret, quote, shell_data);
		}
		else
			ft_strncat(&ret, input[i++], 1);
	}
	if (ret && ft_strlen(ret) <= 3 && ft_strchr(ret, '\''))
		ret = handle_apix_case(ret);
	return (ret);
}
