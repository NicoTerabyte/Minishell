/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/02 18:02:57 by lnicoter         ###   ########.fr       */
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
			printf("prima qui\n");
			ft_strncat(ret, input[i++], 1); //con "'$us'" va qui ret = '\0'
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

	//"'$us'"
	i = 0;
	ret = ft_strdup("");
	while (input[i] != '\0')
	{
		printf("input %c\n", input[i]);
		if (input[i] == '$')
		{
			printf("1\n");
			ret = manage_dollar_norm(input, &i, ret, shell_data);
		}
		else if (input[i] == '\'' || input[i] == '"')
		{
			printf("2\n");
			quote = input[i++];
			i += quote_logic_norm(&input[i], &ret, quote, shell_data);
			printf("ret %s\n", ret);
		}
		else
		{
			printf("3\n");
			ft_strncat(&ret, input[i++], 1);
		}
	}
	return (ret);
}
