/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/17 17:51:45 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**splitcmd;
	char	*syntax;
	t_data	*shell_data;
	t_declaration	*identity;

	identity = (t_declaration *)malloc(sizeof(t_declaration));
	shell_data = (t_data *)malloc(sizeof(t_data));
	if (!identity || !shell_data)
	{
		free(identity);
		free(shell_data);
		exit(0);
	}
	if(!copy_env(envp, shell_data))
	{
		free(identity);
		free(shell_data);
		exit(0);
	}
	(void)argc;
	(void)argv;
	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		syntax = fix_syntax(str);
		splitcmd = ft_split(syntax, ' ');
		printf("input : %s \n", syntax);
		parser(splitcmd);
		builtin_reader(splitcmd, shell_data, identity);
		free_matrix(splitcmd);
		free(syntax);
	}
}
