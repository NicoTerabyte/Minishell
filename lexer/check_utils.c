/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 17:16:43 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/06 17:20:28 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int not_op(char *c)
{
	if ((c[0] != '|' && c[1] != '|') || (c[0] != '&' && c[1] != '&') || c[0] != '|')
		return (c[0] >= 32 && c[0] <= 126);
	return (0);
}

int is_one_char(char *c)
{
	if ((c[0] == '|' && c[1] == ' ') || (c[0] == '&' && c[1] == ' ') || (c[0] == '<' && c[1] == ' ') || (c[0] == '>' && c[1] == ' '))
		return (1);
	return (0);
}

int is_two_char(char *c)
{
	if ((c[0] == '|' && c[1] == '|') || (c[0] == '&' && c[1] == '&') || (c[0] == '<' && c[1] == '<') || (c[0] == '>' && c[1] == '>'))
		return (1);
	return (0);
}

int is_double(char *s, int *i)
{
	if (is_one_char(&s[*i]))
		if (is_one_char(&s[*i + 2]) || is_two_char(&s[*i + 2]))
			return (1);
	if (is_two_char(&s[*i]))
		if (is_one_char(&s[*i + 3]) || is_two_char(&s[*i + 3]))
			return (1);
	return (0);
}

void	del(void *str)
{
	free(str);
}
