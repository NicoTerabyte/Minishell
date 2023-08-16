/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:34:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/08/08 16:16:12 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_oldpwd(t_data *shell_data)
{
	char	*new_value;
	char	*final_string;
	int		i;

	new_value = getcwd(0, 0);
	i = -1;
	while (shell_data->copy_env[++i])
	{
		if (ft_strncmp(shell_data->copy_env[i], "OLDPWD", 6) == 0)
		{
			final_string = ft_strjoin("OLDPWD=", new_value);
			//free(shell_data->copy_env[i]);
			shell_data->copy_env[i] = final_string;
			free(new_value);
			return ;
		}
	}
	printf("Qualcosa e' andato storto\n");
}

void	update_pwd(t_data *shell_data)
{
	char	*new_value;
	char	*final_string;
	int		i;

	new_value = getcwd(0, 0);
	i = -1;
	while (shell_data->copy_env[++i])
	{
		if (ft_strncmp(shell_data->copy_env[i], "PWD", 3) == 0)
		{
			final_string = ft_strjoin("PWD=", new_value);
			//free(shell_data->copy_env[i]);
			shell_data->copy_env[i] = final_string;
			free(new_value);
			return ;
		}
	}
	printf("Qualcosa e' andato storto\n");
}

void	ft_cd(char **command_line, t_data *shell_data)
{
	char	*home;
	//int		i;

	//	i = 0;
	update_oldpwd(shell_data);
	home = getenv("HOME");
	if (command_line[1] != NULL && !ft_strcmp(command_line[1], "$HOME"))
	{
		chdir(home);
		update_pwd(shell_data);
	}
	else if (!command_line[1])
	{
		chdir(home);
		update_pwd(shell_data);
	}
	else
	{
		chdir(command_line[1]);
		update_pwd(shell_data);

	}
	//exit(0);
}
