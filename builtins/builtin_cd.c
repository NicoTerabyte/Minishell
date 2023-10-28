/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 16:34:03 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/28 17:44:12 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	update_oldpwd(t_mini *mini)
{
	char	*new_value;
	char	*final_string;
	int		i;

	new_value = getcwd(0, 0);
	i = -1;
	//shell_data->copy_env
	while (mini->env[++i])
	{
		//shell_data->copy_env
		if (ft_strncmp(mini->env[i], "OLDPWD", 6) == 0)
		{
			final_string = ft_strjoin("OLDPWD=", new_value);
			//shell_data->copy_env
			free(mini->env[i]);
			//shell_data->copy_env
			mini->env[i] = ft_strdup(final_string);
			free(final_string);
			break ;
		}
	}
	free(new_value);
}

void	update_pwd(t_mini *mini)
{
	char	*new_value;
	char	*final_string;
	int		i;

	new_value = getcwd(0, 0);
	i = -1;
	//shell_data->copy_env[++i]
	while (mini->env[++i])
	{
		//shell_data->copy_env[i]
		if (ft_strncmp(mini->env[i], "PWD", 3) == 0)
		{
			final_string = ft_strjoin("PWD=", new_value);
			free(mini->env[i]);
//			free(env[i]);
			mini->env[i] = ft_strdup(final_string);
			free(final_string);
			break ;
		}
	}
	free(new_value);
}
/*
	cambiamenti che intendo fare su cd:
	1) intepretazione migliore dell'env
	2) abolizione di shell_data nel caso io la utilizzi solo per l'env
cosa da fare rimanenti:
	1) usare env_container aggiornare l'env ed usare come si deve
		per cambiare le parti con shell_data grazie a env_container
		che ha l'env sempre aggiornato quindi mi raccomando
	2) implementa action 2 che dovrebbe liberare bene lo spazio
		della matrice per poi sistemarla di nuovo
		nel dubbio ricontrolla bene env_container
*/
int	ft_cd(char **command_line, t_mini *mini)
{
	char	*home;

	update_oldpwd(mini);
	home = getenv("HOME");
	if (command_line != NULL && !ft_strcmp(command_line[0], "$HOME"))
	{
		chdir(home);
		update_pwd(mini);
	}
	else if (!command_line)
	{
		chdir(home);
		update_pwd(mini);
	}
	else
	{
		chdir(command_line[0]);
		update_pwd(mini);
	}
	return (0);
}
