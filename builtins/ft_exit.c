/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 14:37:44 by mlongo            #+#    #+#             */
/*   Updated: 2023/09/08 16:39:57 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	ft_isstrnum(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_exit(char **args)
{
	int	len_args;
	int	exit_value;

	len_args = 0;
	if (args)
		while (args[len_args])
			len_args++;
	if (len_args == 0)
	{
		ft_free_all(var_container(NULL, NULL, GET_TOKENS), var_container(NULL, NULL, GET_TREE));
		printf("exit\n");
		exit(0);
	}
	else
	{
		if (ft_isstrnum(args[0]))
		{
			if (len_args == 1)
			{
				exit_value = ft_atoi(args[0]);
				ft_free_all(var_container(NULL, NULL, GET_TOKENS), var_container(NULL, NULL, GET_TREE));
				printf("exit\n");
				exit(exit_value);
			}
			else
			{
				printf("exit\nminishell: exit: too many arguments\n");
				exit_value = ft_atoi(args[0]);
				return (exit_value);
			}
		}
		else
		{
			printf("exit\nminishell: exit: %s: numeric argument required\n", args[0]);
			ft_free_all(var_container(NULL, NULL, GET_TOKENS), var_container(NULL, NULL, GET_TREE));
			exit (2);
		}
	}
}
