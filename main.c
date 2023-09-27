/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/09/25 21:23:41 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	char			**splitcmd;
	//char			*syntax;
	t_data			*shell_data;

	init_structs(&shell_data, envp);

	(void)argc;
	(void)argv;
	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		splitcmd = ft_split(str, ' ');
		//syntax = fix_syntax(str); //il fottuto problema!!!!
		parser(splitcmd);
		builtin_reader(splitcmd, shell_data);
		free_matrix(splitcmd);
		//free_matrix(shell_data->copy_env);
	}
	//i free veri vanno fatti quando verrà implementato l'exit
	//e i SEGNALI SOPRATUTTO
	free_matrix(shell_data->copy_env);
}

