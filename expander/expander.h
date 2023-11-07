/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/07 16:53:00 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_H
# define EXPANDER_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

#include "../minishell.h"
# define AND 0
# define OR 1
# define PIPE 2
# define REDIRECTION_INPUT 3
# define REDIRECTION_INPUT_HERE_DOC 4
# define REDIRECTION_OUTPUT_TRUNC 5
# define REDIRECTION_OUTPUT_APPEND 6
# define DOUBLE_QUOTES 7
# define SINGLE_QUOTES 8

// abuonomo
char			*expander(t_mini *mini, char *input);
char			*translate_wild(t_mini *mini, char *input);
int				is_wildcard(char *input);
char			*handle_apix_case(char *ret);
char			**matrix_directory(t_mini *mini);
char			*ft_strjoin_wild(char const *s1, char const *s2);
char			*get_extension(const char *filename);
int				ft_strcmp_env(const char *input, const char *env);
struct dirent	**matrix_file(t_mini *mini);
void			stampaMatriceChar(char **matrice);
char			*current_dir(void);
char			*ft_strcpy(char *dest, char *src);
char			*launch_exp_wild(t_mini *mini, char *input);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
void			ft_strncat(char **dest, char c, int nb);
char			*ft_strcat(char *dest, char *src);
int				jump_to_next(char *str);
char			*expand_env_variable(t_mini *mini, const char *var_name);
char			*expand_variable(t_mini *mini, char *input, int *i);
char			*realloc_concat_free_norm(char *ret, char *v);
char			*manage_dollar_norm(char *input, int *i,
					char *ret, t_mini *mini);
int				quote_logic_norm(char *input, char **ret,
					char quote, t_mini *mini);

char			*ft_wildcard(char *input, t_mini *mini);
int				filter_word(char *input, char *filename, t_mini *mini);
int				word_middle_filter(char *filter, char *filename, int *i);
int				word_start_filter(char *filter, char *filename, int *i);
int				word_end_filter(char *filter, char *filename, int *i);
char			*expand_strbefore(char *input, int i, t_mini *mini);
int				move_to_wildcard(char *input);
int				is_wildcard_present(char *input);
int				check_wildcard_before(char *input, int i);
#endif
