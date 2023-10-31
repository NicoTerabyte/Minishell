/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/10/31 18:02:39 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include "../minishell.h"
# define AND 0
# define OR 1
# define PIPE 2
# define REDIRECTION_INPUT 3
# define REDIRECTION_INPUT_HERE_DOC 4
# define REDIRECTION_OUTPUT_TRUNC 5
# define REDIRECTION_OUTPUT_APPEND 6
# define DOUBLE_QUOTES 7
# define SINGLE_QUOTES 8

// typedef struct s_data
// {
// 	char			*path;
// 	char			*old_path;
// 	char			**copy_env;
// 	struct dirent	**file;
// } t_data;


// void	insert_in_env(t_data shell_data, char *final_string, t_declaration *values);
// abuonomo
char			*expander(t_mini *mini, char *input);
// char			*translate_wild(t_mini *mini, char *input);
// int				is_wildcard(char *input);
// char			**matrix_directory(t_mini *mini);
// char			*ft_strjoin_wild(char const *s1, char const *s2);
// char			*get_extension(const char *filename);
int				ft_strcmp_env(const char *input, const char *env);
// struct dirent	**matrix_file(t_mini *mini);
// void			stampaMatriceChar(char **matrice);
// char			*current_dir(void);
char			*ft_strcpy(char *dest, char *src);
char			*launch_exp_wild(t_mini *mini, char *input);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
char			*ft_strncat(char *dest, char *src, int nb);
char			*ft_strcat(char *dest, char *src);
#endif
