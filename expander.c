/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/29 21:54:23 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp_env(const char *input, const char *env)
{
	while (*env != '=' && (*input != ' ' || *input != '$'))
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

int	jump_to_next(char *str)
{
	int i;

	i = 0;
	while(str[i]){
		if(str[i] == ' ' || str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}
char *expander(t_data *shell_data, char *input)
{
	char *ret;
	int i;
	int k;

	i = 0;
	ret = ft_strdup("");
	while (input[i] != '\0')
	{
		if(input[i] == '$'){
			i++;
			k = 0;
			while(shell_data->copy_env[k] != NULL){
				printf("Valore di input: %s\n",&input[i]);
				printf("Valore di copy_env: %s\n", shell_data->copy_env[k]);
				printf("Valore di ft_strcmp: %d\n",ft_strcmp_env(&input[i], shell_data->copy_env[k]));
				if(ft_strcmp_env(&input[i], shell_data->copy_env[k]) == 0){
					printf("PRE REALLOC: %s\n",ret);
					ret = realloc(ret, ft_strlen(ret) + ft_strlen(ft_strchr(shell_data->copy_env[k], '=') + 1));
					printf("POST REALLOC: %s\n",ret);
					strncat(ret, strchr(shell_data->copy_env[k],'=') + 1, ft_strlen(strchr(shell_data->copy_env[k],'=') + 1));
					printf("POST COPY: %s\n",ret);
					break;
				}
				k++;
			}
			printf("VALORE DI I PRE FUNC: %d\n",i);
			i += jump_to_next(&input[i]);
			printf("VALORE DI I POST FUNC: %d\n",i);
		}
		else{
			printf("VALORE DI RET pre STRC: %s\n",ret);
			strncat(ret, &input[i],1);
			printf("VALORE DI RET Post STRC: %s\n",ret);
			i++;
		}
	}
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
