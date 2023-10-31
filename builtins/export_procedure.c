/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_procedure.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 14:29:18 by lnicoter          #+#    #+#             */
/*   Updated: 2023/10/31 11:13:53 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	phase1(t_data *shell_data, char **final_string)
// {
// 	char	*support_str;
// 	if (shell_data->identity->concatenation != 0)
// 		*final_string = ft_strjoin_damn_you_leaks(*final_string, "=");
// 	if (!ft_strchr(shell_data->identity->value, '\"') && !ft_strchr(shell_data->identity->value, '\''))
// 	{
// 		*final_string = ft_strjoin_damn_you_leaks(*final_string, "\""); //fare funzione per liberare e rifare
// 		*final_string = ft_strjoin_damn_you_leaks(*final_string, shell_data->identity->value); //non liberi la stringa precedente
// 		*final_string = ft_strjoin_damn_you_leaks(*final_string, "\"");
// 	}
// 	else if (ft_strchr(shell_data->identity->value, '\''))
// 	{
// 		support_str = i_hate_this_strcpy_for_apix(NULL, shell_data->identity->value);
// 		*final_string = ft_strjoin_damn_you_leaks(*final_string, support_str);
// 		free(support_str);
// 	}
// 	else
// 		*final_string = ft_strjoin_damn_you_leaks(*final_string, shell_data->identity->value);
// 	printf("daje testamo %s\n", *final_string);
// }

// void	phase2(char **final_string)
// {
// 	*final_string = ft_strjoin_damn_you_leaks(*final_string, "=");
// 	*final_string = ft_strjoin_damn_you_leaks(*final_string, "\"");
// 	*final_string = ft_strjoin_damn_you_leaks(*final_string, "\"");
// }


//queste potrebbero servire però

// void	updating(char	***separg)
// {
// 	int	plus_finder;

// 	plus_finder = -1;
// 	printf("valore di separg %s\n", (*separg)[0]);
// 	while((*separg)[0][++plus_finder])
// 	{
// 		printf("first try %c\n", (*separg)[0][plus_finder]);
// 		if ((*separg)[0][plus_finder] == '+')
// 			(*separg)[0][plus_finder] = '\0';
// 	}
// }

// void	list_update(t_data *shell_data, int conc, char **com_line, int i)
// {
// 	char	**separg;

// 	if (check_arguments_validation(com_line[i]))
// 	{
// 		if (ft_strchr(com_line[i], '='))
// 		{
// 			conc = 1;
// 			separg = split_bt_nt_t_mc(com_line[i], '=');
// 		}
// 		else
// 			separg = ft_split(com_line[i], '=');
// 		if (ft_strchr(separg[0], '+'))
// 		{
// 			conc = 2;
// 			updating(&separg);
// 		}
// 		insert_declaration(shell_data, conc, separg[0], separg[1]);
// 		conc = 0;
// 	}
// 	free_matrix(separg);
// }
