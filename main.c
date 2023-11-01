/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/01 18:10:41 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printEnvironment(char **envp)
{
	int i;

	i = 0;
	while (envp[i] != NULL) {
		printf("%s\n", envp[i]);
		i++;
	}
}


int	main(int argc, char **argv, char **envp)
{
	char	*ret;
	char	*str;
	char	**splitcmd;
	char	*syntax;
	t_data		*shell_data;
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
		str = readline("\nminishell> ");
		ret = launch_exp_wild(shell_data, str);
		free(str);
		free(ret);
	}
}
