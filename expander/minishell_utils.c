/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 17:46:34 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/06 15:45:14 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp_env(const char *input, const char *env)
{
	while (*env != '=' && (*input != ' ' || *input != '$'))
	{
		if (*input != *env)
			return (1);
		input++;
		env++;
	}
	return (*env != '=' || *input != '\0');
}
