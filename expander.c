/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/21 21:14:07 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp_env(const char *input, const char *env)
{
	while (*env != '=' && *input != '\0')
	{
		if (*input != *env)
		{
			return 1;
		}
		input++;
		env++;
	}
	return (*env != '=' || *input != '\0');
}

char *handle_single_quote(char *input, char **ret, int *ret_index)
{
	input++;
			while(*input != 39){
				*ret += *ret_index;
				**ret = *input;
				*input+=1;
				*ret_index+=1;
			}
	input++;
	return input;
}

char *translate_exp(t_data *shell_data, char *input)
{
	int i = 0;
	int var_index;
	char *ret = malloc(ft_strlen(input) + 1);
	int ret_index;
	char var[100];
	char *value_start;

	ret_index = 0;
	if (!ret)
		return ("ERRORE DI ALLOCAZIONE");
	while (*input)
	{
		if(*input == 39)
			input = handle_single_quote(input, &ret, &ret_index);
		else if (*input == '$' && *(input + 1) && ft_isalpha(*(input + 1)))
		{
			input++;
			var_index = 0; // Indice per la posizione corrente nel nome della variabile
			while (ft_isalnum(*input) || *input == '_')
				var[var_index++] = *input++;
			var[var_index] = '\0'; // Termina la stringa di nome variabile
			i = 0;
			while (shell_data->copy_env[i])
			{
				if (ft_strcmp_env(var, shell_data->copy_env[i]) == 0)
				{
					value_start = strchr(shell_data->copy_env[i], '=') + 1;
					while (*value_start)
						ret[ret_index++] = *value_start++; // Copia il valore della variabile nell'output
					break;
				}
				i++;
			}
		}
		else if(*input == 34){
			input++;
			while(*input != 34)
			{
				if (*input == '$' && *(input + 1) && ft_isalpha(*(input + 1)))
		{
			input++;
			var_index = 0; // Indice per la posizione corrente nel nome della variabile
			while (ft_isalnum(*input) || *input == '_')
				var[var_index++] = *input++;
			var[var_index] = '\0'; // Termina la stringa di nome variabile
			i = 0;
			while (shell_data->copy_env[i])
			{
				if (ft_strcmp_env(var, shell_data->copy_env[i]) == 0)
				{
					value_start = strchr(shell_data->copy_env[i], '=') + 1;
					while (*value_start)
						ret[ret_index++] = *value_start++; // Copia il valore della variabile nell'output
					break;
				}
				i++;
			}
		}
				ret[ret_index++] = *input++;
			}
			input++;
		}
		else
			ret[ret_index++] = *input++; // Copia il carattere normale nell'output
	}
	ret[ret_index] = '\0'; // Termina la stringa di output
	return ret;
}




void stampaMatriceChar(char **matrice) {
    int riga = 0;
    while (matrice[riga] != NULL) {
        int colonna = 0;

        while (matrice[riga][colonna] != '\0') {
            printf("%c ", matrice[riga][colonna]);
            colonna++;
        }

        printf("\n");
        riga++;
    }
}
