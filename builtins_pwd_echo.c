/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd_echo.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:34:36 by lnicoter          #+#    #+#             */
/*   Updated: 2023/09/14 18:20:23 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_pwd()
{
	char	pwd[4096];

	getcwd(pwd, sizeof(pwd));
	printf("%s\n", pwd);
	exit(0);
}

static int		echo_case(char **command_line)
{
	if (!command_line[1])
		return (1);
	else if (!command_line[2] && !ft_strcmp(command_line[1], "-n"))
		return (2);
	return (0);
}

static void	echo_printer(char **command_line, int flag, int mat_size, int i)
{
	if (flag == 1)
		i++;
	while (command_line[mat_size])
		mat_size++;
	while (command_line[++i])
	{
		printf("%s", command_line[i]);
		if (i < mat_size - 1)
			printf(" ");
	}
	if (flag == 0)
		printf("\n");
}

static int	flag_checker(char **command_line, int flag)
{
	int	n_counter;

	n_counter = 1;
	if (command_line[1][0] == '-' && command_line[1][1] == 'n')
	{
		flag = 1;
		while(command_line[1][++n_counter])
		{
			if (command_line[1][n_counter] != '\0' && command_line[1][n_counter] != 'n')
			{
				flag = 0;
			}
		}
	}
	return (flag);
}

void	ft_echo(char **command_line)
{
	int	i;
	int	flag;
	int	mat_size;

	mat_size = 0;
	flag = 0;
	i = 0;
	if (echo_case(command_line) == 2)
		return ;
	else if (echo_case(command_line) == 1)
	{
		printf("\n");
		return ;
	}
	flag = flag_checker(command_line, flag);
	echo_printer(command_line, flag, mat_size, i);
}

void	builtin_reader(char **command_line, t_data *shell_data, t_declaration **identity) //aggiornare con struct
{
	char	pwd[4096];

	printf("lettura %s\n", command_line[0]);
	if (!ft_strcmp(command_line[0], "pwd" ))
	{
		getcwd(pwd, sizeof(pwd));
		printf("%s\n", pwd);
	}
	if (!ft_strcmp(command_line[0], "echo" ))
		ft_echo(command_line);
	if (!ft_strcmp(command_line[0], "cd"))
		ft_cd(command_line, shell_data);
	if (!ft_strcmp(command_line[0], "env"))
		ft_env(shell_data);
	if (!ft_strcmp(command_line[0], "export"))
		ft_export(command_line, shell_data, identity);
}
