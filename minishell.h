/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/07 19:49:25 by abuonomo         ###   ########.fr       */
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
# include <dirent.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <stdarg.h>
# include <sys/wait.h>
# include <termios.h>
# include "./libft/libft.h"
# include "global.h"
# define AND 0
# define OR 1
# define PIPE 2
# define REDIRECTION_INPUT 3
# define REDIRECTION_INPUT_HERE_DOC 4
# define REDIRECTION_OUTPUT_TRUNC 5
# define REDIRECTION_OUTPUT_APPEND 6
# define DOUBLE_QUOTES 7
# define SINGLE_QUOTES 8

typedef struct s_data
{
	char			*path;
	char			*old_path;
	char			**copy_env;
	struct dirent	**file;
}	t_data;

typedef struct s_declaration
{
	int						concatenation;
	char					*name;
	char					*value;
	struct s_declaration	*next;
}	t_declaration;

int				cmd_name(char *str);
void			parser(char **splitcmd);
int				count_syntax(char *str);
char			*fix_syntax(char *str);
int				free_matrix(char **s);
void			builtin_reader(char **command_line, t_data *shell_data,
					t_declaration *identity);
void			ft_echo(char **command_line);
void			ft_cd(char **command_line, t_data *shell_data);
void			ft_env(t_data *shell_data);
int				copy_env(char **env, t_data *mini_data);
void			ft_pwd(void);
void			update_oldpwd(t_data *shell_data);
void			update_pwd(t_data *shell_data);
int				ft_strcmp(const char *s1, const char *s2);
void			*ft_realloc(void *p, size_t size, int dim, int new_dim);
void			ft_export(char **command_line, t_data *shell_data,
					t_declaration *identity);
void			print_export(char **export_matrix);
void			sort_and_print_export(t_data *shell_data);
char			**setting_the_matrix(t_data *shell_data);
int				env_rows(t_data *shell_data);
int				put_arguments_in_list(t_declaration *identity,
					char *command_line);
void			insert_declaration(t_declaration **list, int concatenation,
					const char *name, const char *value);
void			print_list(t_declaration *list);
void			arguments_separation(char **command_line, int conc,
					t_declaration **identity);
void			add_env(t_data *shell_data, t_declaration **values);
void			super_strjoin(t_data *shell_data, t_declaration *values);
char			*expander(t_data *shell_data, char *input);
char			*handle_apix_case(char *ret);
char			**matrix_directory(t_data *shell_data);
int				ft_strcmp_env(const char *input, const char *env);
void			stampaMatriceChar(char **matrice);
char			*ft_strcpy(char *dest, char *src);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
void			ft_strncat(char **dest, char c, int nb);
char			*ft_strcat(char *dest, char *src);
int				jump_to_next(char *str);
char			*expand_env_variable(t_data *shell_data, const char *var_name);
char			*expand_variable(t_data *shell_data, char *input, int *i);
char			*realloc_concat_free_norm(char *ret, char *v);
char			*manage_dollar_norm(char *input, int *i,
					char *ret, t_data *shell_data);
int				quote_logic_norm(char *input, char **ret,
					char quote, t_data *shell_data);
char			*order_result(char *result);
void			selection_sort(char **array);
void			swapstrings(char **a, char **b);
char			*ft_wildcard(char *input, t_data *mini);
int				filter_word(char *input, char *filename, t_data *mini);
int				word_middle_filter(char *filter, char *filename, int *i);
int				word_start_filter(char *filter, char *filename, int *i);
int				word_end_filter(char *filter, char *filename, int *i);
char			*expand_strbefore(char *input, int i, t_data *mini);
int				move_to_wildcard(char *input);
int				is_wildcard_present(char *input);
int				check_wildcard_before(char *input, int i);
void			close_free_dir(struct dirent *entry,char *dirname,DIR *dir);
void			open_read_getcwd(char **dirname, DIR **dir, struct dirent **entry);
#endif
