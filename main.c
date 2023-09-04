/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/09/04 14:22:40 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static char	*path_create(char *s1, char *s2, char *s3, char *s4, char *s5)
{
	int	i;
	int	j = 0;
	char *str;
	
	str = malloc(strlen(s1) + strlen(s2) + strlen(s3) + strlen(s4)+ strlen(s5) + 1);
	i = 0;
	while (s1[j])
		str[i++] = s1[j++];
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	j = 0;
	while (s3[j])
		str[i++] = s3[j++];
	j = 0;
	while (s4[j])
		str[i++] = s4[j++];
	j = 0;
	while (s5[j])
		str[i++] = s5[j++];
	str[i] = 0;
	return (str);
}

static char	*create(char *s1)
{
	int	i;
	char *str;
	
	str = malloc(strlen(s1) + 1);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static char	*mini(void)
{
  	char	pwd[4096];
	char	*path;
	char	*name;
	char	**dir;

    getcwd(pwd, sizeof(pwd));
	dir = ft_split(pwd, '/');
	name = create(dir[2]);
	while (*dir)
		dir++;
	path = path_create("\033[31;49;3;1m", name, "@Mini$hell🔥:\033[32m~/", *--dir, "$ \033[0m");
	return (path);
}

int main()
{
	char 	*str;
	char	*fixed;
	char	*path;
	//char	**input;

	while (1)
	{
		while (1)
		{
			path = mini();
			str = readline(path);
			add_history(str);
			fixed = fix_syntax(str);
			printf("input : %s \n", fixed);
			if (!check(fixed))
			{
				printf("Syntax error\n");
				break;
			}
			//printf("%d\n", check_parentheses(fixed, &i));
			printf("tt ok!\n");
			// input = ft_split(fixed, ' ');
			// parser(input);
			// free_matrix(input);
			free(path);
			free(str);
		}
	}
}
