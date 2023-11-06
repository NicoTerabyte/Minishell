/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/06 15:06:20 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	char			*ret;
	char			**splitcmd;
	char			*syntax;
	t_data			*shell_data;
	t_declaration	*identity;

	identity = (t_declaration *)malloc(sizeof(t_declaration));
	shell_data = (t_data *)malloc(sizeof(t_data));
	if (!identity || !shell_data)
	{
		free(identity);
		free(shell_data);
		exit(0);
	}
	if (!copy_env(envp, shell_data))
	{
		free(identity);
		free(shell_data);
		exit(0);
	}
	(void)argc;
	(void)argv;
	while (1)
	{
		str = readline("\nminishell> ");
		ret = ft_wildcard(str, shell_data);
		//ret = expander(str,shell_data);
		if(!ret)
			;
		else
			printf("%s", ret);
		free(str);
		free(ret);
	}
}
