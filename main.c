/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/08/06 19:57:23 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	//TUTTO A PUTTANE CHECK I PROCESSI
	char	*str;
	char	**splitcmd;
	t_data	*shell_data;
	int		copy_flag;

	shell_data = malloc(sizeof(shell_data)); //aggiunta superflua
	(void)argc;
	(void)argv;
	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		splitcmd = ft_split(fix_syntax(str), ' ');
		printf("input : %s \n", fix_syntax(str));
		parser(splitcmd);
		/*char *str = "..";
		int fd = fork();
		if (fd == 0)
			ft_cd(&str);
		int fd1 = fork();
		if (fd1 == 0)
			ft_pwd();*/
		builtin_reader(splitcmd, envp, shell_data);
		free_matrix(splitcmd);
		free(str);
	}
}
