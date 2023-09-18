/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/18 18:52:48 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Searching File with Particular Extension and ‘*’
	//You can search any file by using the asterisk (*) and the file extension.
	//If you want to search all files with the ‘.txt’ extension from the current directory
	//then run the following command from the terminal. Here, the filename can be any
	//character(s) and any number of characters.

char	*extension(t_data *shell_data, char *wildstring)
{
	char *ret;
	int i;
	char *extension;

	i = 0;
	ret = "";
	while (shell_data->dir_list[i] != NULL)
	{
		extension = get_extension(shell_data->dir_list[i]);
		if(extension && ft_strcmp(extension,wildstring) == 0)
			ret = ft_strjoin_wild(ret,shell_data->dir_list[i]);
		i++;
	}
	return (ret);
}

//Searching Specific File with Filename and ‘*’
	//‘ls’ command is used to find out the list of files and folders of the current directory.
	//‘ls a*’ command will search and print all filenames of the current directory that
	//starts with the character, ‘a’.

char	*filename(t_data *shell_data, char *wildstring)
{
	char *ret;
	ret = malloc(mcharnum(shell_data) * sizeof(char));
	return (wildstring);
}

	//You can use the asterisk (*) for matching any filename partially. The following command
	//will remove the file which contains the ‘test’ word in any part of the filename.

char	*partial(t_data *shell_data, char *wildstring)
{
	int i;
	char *ret;

	printf("PARTIAL");
	i = 0;
	ret = "";
	while (shell_data->dir_list[i] != NULL)
	{
		if(shell_data->dir_list[i][0] != '.')
		{
		if (ft_strnstr(shell_data->dir_list[i], wildstring, strlen(shell_data->dir_list[i])) != NULL){
			ret = ft_strjoin_wild(ret,shell_data->dir_list[i]);
		}
		}
		i++;
	}
	return (ret);
}

char	*translate_wild(t_data *shell_data, char *input){

	char	*wildstring;
	int		i;
	int		x;

	i = 0;
	x = 0;
	wildstring = malloc(ft_strlen(input) + 1);
	while (input[i])
	{
		if (input[i] == '*')
		{
			i++;
			if (input[i] == '.')
			{
				i++;
				while (ft_isalpha(input[i]))
					wildstring[x++] = input[i++];
				wildstring[x] = 0;
				return (extension(shell_data, wildstring));
			}else if(ft_isalpha(input[i]))
			{
				while(ft_isalpha(input[i]) || input[i] == '*'){
					if(input[i] == '*'){
						wildstring[x] = 0;
						return partial(shell_data, wildstring);
					}
					wildstring[x++] = input[i++];
				}
				wildstring[x] = 0;
				return (filename(shell_data, wildstring));
			}
		}
		i++;
	}
}
