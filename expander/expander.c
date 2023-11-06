/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/06 15:43:06 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quote_logic_norm(char *input, char **ret, char quote, t_mini *mini)
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
			*ret = manage_dollar_norm(input, &i, *ret, mini);
		else
			ft_strncat(ret, input[i++], 1);
	}
	return (i);
}

char	*expander(t_mini *mini, char *input)
{
	char	*ret;
	int		i;
	char	quote;

	i = 0;
	ret = ft_calloc(1, sizeof(char));
	while (input[i] != '\0')
	{
		if (input[i] == '$')
			ret = manage_dollar_norm(input, &i, ret, mini);
		else if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			i += quote_logic_norm(&input[i], &ret, quote, mini);
		}
		else
			ft_strncat(&ret, input[i++], 1);
	}
	if (ret && ft_strlen(ret) <= 3 && ft_strchr(ret, '\''))
		ret = handle_apix_case(ret);
	return (ret);
}
