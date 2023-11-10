/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils3_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 16:23:10 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/10 16:23:25 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander_simple_cmd_args(char **args, t_mini *mini)
{
	int	i;

	i = 0;
	while (args[i])
	{
		args[i] = expander(mini, args[i]);
		i++;
	}
}
