/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/09/09 17:16:47 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			*str;
	char			**splitcmd;
	char			*syntax;
	t_data			*shell_data;
	t_declaration	*identity;
	int				i;

	i = 0;
	init_structs(&identity, &shell_data, envp);
	(void)argc;
	(void)argv;
	while (1)
	{
		i = 0;
		str = readline("minishell> ");
		add_history(str);

		//syntax = fix_syntax(str); //il fottuto problema!!!!
		printf("check del readline\n");
		if (str && *str)
			splitcmd = ft_split(str, ' ');
		else
		{
			printf("la morte incombe\n");
			return (0);
		}
		while (str[i]) //dopo la quinta aggiunta l'errore si ferma qui
		{
			printf("%c\n", str[i]);
			i++;
		}
		printf("input : %s \n", str);
		parser(splitcmd);
		builtin_reader(splitcmd, shell_data, identity);
		free_matrix(splitcmd);
		//free(syntax);
		printf("Again\n");
	}
	//i free veri vanno fatti quando verrà implementato l'exit
	//e i SEGNALI SOPRATUTTO
	free_matrix(shell_data->copy_env);
}
