/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exp_wild.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 20:57:02 by abuonomo          #+#    #+#             */
/*   Updated: 2023/10/31 17:57:00 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *launch_exp_wild(t_mini *mini, char *input)
{
	char *ret;
	int i;

	i = 0;
	ret = expander(mini, input);
	return (ret);
}
