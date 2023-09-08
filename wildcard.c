/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by abuonomo          #+#    #+#             */
/*   Updated: 2023/09/08 13:06:59 by abuonomo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_wildcard(t_data *shell_data, char *input)
{
	while(*input){
		if(*input == '*')
			return 1;
	}
	return 0;
}

char *translate_exp(t_data *shell_data, char *input){

	char *wildstring = malloc(strlen(input) + 1);
	int i = 0;
	int x = 0;

	while(input[i++]){
		if(input[i] == '*'){
			i++;
			if(input[i] == '.'){
				while(ft_isalpha(input[i]))
					wildstring[x++] = input[i++];
				return extension();
			}else if(ft_isalpha(input[i]))
			{
				while(ft_isalpha(input[i]) || input[i] == '*'){
					if(input[i] == '*')
						return partial();
					wildstring[x++] = input[i++];
				}
				return filename();
			}
		}
	}
}


//Searching Specific File with Filename and ‘*’
	//‘ls’ command is used to find out the list of files and folders of the current directory.
	//‘ls a*’ command will search and print all filenames of the current directory that
	//starts with the character, ‘a’.

//Searching File with Particular Extension and ‘*’
	//You can search any file by using the asterisk (*) and the file extension.
	//If you want to search all files with the ‘.txt’ extension from the current directory
	//then run the following command from the terminal. Here, the filename can be any
	//character(s) and any number of characters.

//Removing File by Partial Match and ‘*’
	//You can use the asterisk (*) for matching any filename partially. The following command
	//will remove the file which contains the ‘test’ word in any part of the filename.
