/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/07/27 17:09:33 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	char *str;
	char **splitcmd;
	while (1)
	{
		str = readline("minishell> ");
		add_history(str);
		splitcmd = ft_split(fix_syntax(str), ' ');
		printf("input : %s \n", fix_syntax(str));
		parser(splitcmd);
		free_matrix(splitcmd);
		free(str);
	}
}
