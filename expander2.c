/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 15:57:22 by abuonomo          #+#    #+#             */
/*   Updated: 2023/11/03 11:39:38 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jump_to_next(char *str)
{
	int	i;
	int	x;

	i = 0;
	while (str[i])
	{
		if (!ft_isalnum(str[i]))
			return (i);
		i++;
	}
	return (i);
}

char	*expand_env_variable(t_data *shell_data, const char *var_name)
{
	int	k;

	k = 0;
	while (shell_data->copy_env[k] != NULL)
	{
		if (ft_strcmp_env(var_name, shell_data->copy_env[k]) == 0)
			return (ft_strdup(strchr(shell_data->copy_env[k], '=') + 1));
		k++;
	}
	return (NULL);
}

char	*expand_variable(t_data *shell_data, char *input, int *i)
{
	int		var_name_len;
	char	*var_name;
	char	*expanded_value;

	(*i)++;
	var_name_len = jump_to_next(&input[*i]);
	var_name = (char *)malloc(var_name_len + 1);
	ft_strncpy(var_name, &input[*i], var_name_len);
	var_name[var_name_len] = '\0';
	*i += var_name_len;
	expanded_value = expand_env_variable(shell_data, var_name);
	free(var_name);
	return (expanded_value);
}

char	*realloc_concat_free_norm(char *ret, char *v)
{
	char	*new_ret;
	size_t	new_lenght;

	new_lenght = ft_strlen(ret) + ft_strlen(v) + 1;
	new_ret = (char *)malloc(new_lenght);
	if (new_ret == NULL)
		return (ret);
	ft_strcpy(new_ret, ret);
	ft_strcat(new_ret, v);
	free(ret);
	return (new_ret);
}

char	*manage_dollar_norm(char *input, int *i, char *ret, t_data *shell_data)
{
	char	*v;

	printf("ret in dollars %s\n", ret);
	v = expand_variable(shell_data, input, i);
	if (v != NULL)
		return (realloc_concat_free_norm(ret, v));
	return (NULL);
}
