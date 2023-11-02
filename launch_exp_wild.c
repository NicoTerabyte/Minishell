/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exp_wild.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:57:02 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/02 14:51:02 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*launch_exp_wild(t_data *shell_data, char *input)
{
	char	*ret;
	int		i;

	i = 0;
	ret = expander(shell_data, input);
	return (ret);
}
