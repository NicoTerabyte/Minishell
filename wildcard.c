/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/18 20:10:48 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *extension(t_data *shell_data, char *wildstring)
{
	char *ret;
	int i;
	char *extension;

	i = 0;
	ret = "";
	while (shell_data->dir_list[i] != NULL)
	{
		extension = get_extension(shell_data->dir_list[i]);
		if (extension && ft_strcmp(extension, wildstring) == 0)
			ret = ft_strjoin_wild(ret, shell_data->dir_list[i]);
		i++;
	}
	return (ret);
}

// Searching Specific File with Filename and ‘*’
// ‘ls’ command is used to find out the list of files and folders of the current directory.
// ‘ls a*’ command will search and print all filenames of the current directory that
// starts with the character, ‘a’.

char *filename(t_data *shell_data, char *wildstring)
{
	char *ret;
	int i;

	ret = "";
	i = 0;
	while (shell_data->dir_list[i] != NULL)
	{
		if (ft_strncmp(shell_data->dir_list[i], wildstring, ft_strlen(wildstring)) == 0)
			ret = ft_strjoin_wild(ret, shell_data->dir_list[i]);
		i++;
	}
	return (ret);
}

char *partial(t_data *shell_data, char *wildstring)
{
	int i;
	char *ret;

	i = 0;
	ret = "";
	while (shell_data->dir_list[i] != NULL)
	{
		if (shell_data->dir_list[i][0] != '.')
		{
			if (ft_strnstr(shell_data->dir_list[i], wildstring, strlen(shell_data->dir_list[i])) != NULL)
				ret = ft_strjoin_wild(ret, shell_data->dir_list[i]);
		}
		i++;
	}
	return (ret);
}

char *translate_wild(t_data *shell_data, char *input)
{
	char *wildstring;
	int i;
	int x;

	i = 0;
	x = 0;
	wildstring = malloc(ft_strlen(input) + 1);

	if (ft_isalpha(input[i]))
	{
		while (input[i] != '*')
			wildstring[x++] = input[i++];
		wildstring[x] = 0;
		return filename(shell_data, wildstring);
	}
	else if (input[i] == '*')
	{
		i++;
		if (input[i] == '.')
		{
			i++;
			while (ft_isalpha(input[i]))
				wildstring[x++] = input[i++];
			wildstring[x] = 0;
			return extension(shell_data, wildstring);
		}
		else
		{
			while (ft_isalpha(input[i]))
				wildstring[x++] = input[i++];
			wildstring[x] = '\0';
			if(input[i] == '*')
				return partial(shell_data, wildstring);
		}
	}
return NULL;
}
