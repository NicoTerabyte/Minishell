/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 21:51:50 by lnicoter          #+#    #+#             */
/*   Updated: 2023/11/05 19:30:31 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_matrix(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	return (0);
}

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] != '\0' && i < n)
	{
		dest[i] = src[i];
		++i;
	}
	if (i < n && src[i] == '\0')
	{
		while (dest[i] != '\0')
		{
			dest[i] = '\0';
			++i;
		}
	}
	return (dest);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void ft_strncat(t_data *shell_data, char c, int nb)
{
    size_t current_len;
    int i;

    if (shell_data->ret_exp != NULL)
        current_len = ft_strlen(shell_data->ret_exp);
    else
        current_len = 0;
	shell_data->ret_exp = (char *)ft_realloc(shell_data->ret_exp, sizeof(char), current_len * sizeof(char), (current_len + nb + 1) * sizeof(char));
    if (shell_data->ret_exp == NULL)
        return;

    // Copy 'nb' characters to the resized block
    i = 0;
    while (i < nb)
    {
        shell_data->ret_exp[current_len + i] = c;
        i++;
    }

    shell_data->ret_exp[current_len + nb] = '\0';
}

char	*handle_apix_case(char *ret)
{
	ret = ft_realloc(ret, sizeof(char), 2, 3);
	ret[0] = '\'';
	ret[1] = '\'';
	ret[2] = '\0';
	return (ret);
}
