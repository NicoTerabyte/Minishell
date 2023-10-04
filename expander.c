/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/10/04 17:59:25 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strcmp_env(const char *input, const char *env)
{
	while (*env != '=' && (*input != ' ' || *input != '$'))
	{
		if (*input != *env)
			return (1);
		input++;
		env++;
	}
	return (*env != '=' || *input != '\0');
}

int jump_to_next(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$' || str[i] == '\'' || str[i] == '\"')
			return (i);
		i++;
	}
	return (i);
}

char *expand_env_variable(t_data *shell_data, const char *var_name)
{
	int k;

	k = 0;
	while (shell_data->copy_env[k] != NULL)
	{
		if (ft_strcmp_env(var_name, shell_data->copy_env[k]) == 0)
			return (ft_strdup(strchr(shell_data->copy_env[k], '=') + 1));
		k++;
	}
	return (NULL);
}

char *expand_variable(t_data *shell_data, char *input, int *i)
{
	int var_name_len;
	char *var_name;
	char *expanded_value;

	var_name_len = jump_to_next(&input[*i]);
	printf("VAR_NAME LEN: %d\n", var_name_len);
	var_name = (char *)malloc(var_name_len + 1);
	printf("INPUT STRING: %s\n", &input[*i]);
	ft_strncpy(var_name, &input[*i], var_name_len);
	var_name[var_name_len] = '\0';
	printf("VAR_NAME STRING: %s\n", var_name);
	*i += var_name_len;
	expanded_value = expand_env_variable(shell_data, var_name);
	free(var_name);
	return (expanded_value);
}

char *reallocConcatFreeNorm(char *ret, char *v)
{
	char *new_ret;
	size_t new_lenght;

	new_lenght = ft_strlen(ret) + ft_strlen(v) + 1;
	new_ret = (char *)malloc(new_lenght);

	if (new_ret == NULL)
		return ret;
	ft_strcpy(new_ret, ret);
	ft_strcat(new_ret, v);
	free(ret);
	return new_ret;
}

char *expander(t_data *shell_data, char *input)
{
	char *ret;
	int i;
	char *v;
	char quote;

	i = 0;
	ret = ft_strdup("");
	while (input[i] != '\0')
	{
		printf("input[%d] = %c\n", i, input[i]);
		if (input[i] == '$')
		{
			i++;
			v = expand_variable(shell_data, input, &i);
			if (v != NULL)
				ret = reallocConcatFreeNorm(ret, v);
		}
		else if (input[i] == '\'' || input[i] == '"')
		{
			quote = input[i++];
			while (input[i] != '\0')
			{
				printf("2input[%d] = %c\n", i, input[i]);
				if (input[i] == quote)
				{
					i++;
					break;
				}
				else if (input[i] == '$' && quote == '"')
				{
					i++;
					v = expand_variable(shell_data, input, &i);
					if (v != NULL)
						ret = reallocConcatFreeNorm(ret, v);
				}
				else
					ft_strncat(ret, &input[i], 1);
				i++;
			}
		}
		else
			ft_strncat(ret, &input[i++], 1);
	}
	return ret;
}
