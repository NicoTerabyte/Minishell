/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 19:24:24 by mlongo            #+#    #+#             */
/*   Updated: 2023/11/10 19:24:25 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check(char *s, t_mini *mini)
{
	int		i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '(')
		{
			if (!check_parentheses(s, &i))
				return (0);
		}
		else if (s[i] == ')' && (s[i + 2] != 0))
		{
			i += 2;
			if (!is_op_or_red(s, &i))
				return(0);
			i -= 2;
		}
		else if (s[i] == '\'' || s[i] == '"')
		{
			if (!check_quote(s))
				return (0);
		}
		else if (is_op_or_red(s, &i))
		{
			if (!check_operator(s, &i) || is_op_or_red(s, &i) < 0)
				return (0);
			if (s[i] == '<' && s[i + 1] == '<')
			{
					handle_here_doc(create_del(&s[i + 3]), mini);
					if (g_last_exit_status_cmd == 130)
						return (0);
			}
		}
	}
	return (1);
}
