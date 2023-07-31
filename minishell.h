/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/07/28 16:45:30 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# define AND 0
# define OR 1
# define PIPE 2
# define REDIRECTION_INPUT 3
# define REDIRECTION_INPUT_HERE_DOC 4
# define REDIRECTION_OUTPUT_TRUNC 5
# define REDIRECTION_OUTPUT_APPEND 6
# define DOUBLE_QUOTES 7
# define SINGLE_QUOTES 8

size_t	ft_strlen(const char *s);
int		ft_islower(int c);
int		ft_isupper(int c);
int		ft_isalpha(int c);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
int		free_matrix(char **s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);

int		cmd_name(char *str);
void	parser(char **splitcmd);
int		count_syntax(char *str);
char	*fix_syntax(char *str);

#endif
