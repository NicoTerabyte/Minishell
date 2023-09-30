/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/30 23:58:50 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp_env(const char *input, const char *env)
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

int	jump_to_next(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '$'
			|| str[i] == '\'' || str[i] == '\"')
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

	var_name_len = jump_to_next(&input[*i]);
	var_name = (char *)malloc(var_name_len + 1);
	ft_strncpy(var_name, &input[*i], var_name_len);
	var_name[var_name_len] = '\0';
	*i += var_name_len;
	expanded_value = expand_env_variable(shell_data, var_name);
	free(var_name);
	return (expanded_value);
}

char	*expander(t_data *shell_data, char *input)
{
	char	*ret;
	int		i;
	char	*v;
	int		quote;

	quote = 0;
	i = 0;
	ret = ft_strdup("");
	while (input[i] != '\0')
	{
		if (input[i] == '\"')
		{
			quote = !quote;
			i++;
		}
		if (input[i] == '\'' && quote == 0)
		{
			i++;
			while (input[i] != '\'')
				ft_strncat(ret, &input[i++], 1);
			i++;
		}
		if (input[i] == '$')
		{
			i++;
			v = expand_variable(shell_data, input, &i);
			if (v != NULL)
			{
				ret = ft_realloc(ret, ft_strlen(ret) + ft_strlen(v) + 1);
				ft_strcat(ret, v);
				free(v);
			}
		}
		else
			ft_strncat(ret, &input[i++], 1);
	}
	return (ret);
}
