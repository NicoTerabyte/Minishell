/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/01 17:38:12 by abuonomo         ###   ########.fr       */
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
# include "./libft/libft.h"
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
} t_data;

typedef struct s_declaration
{
	int						concatenation; //true o false
	char					*name; //nome della variabile da inserire nell'export
	char					*value; //il valore di quest'ultima
	struct	s_declaration	*next; //la variabile successiva
}	t_declaration;

int		cmd_name(char *str);
void	parser(char **splitcmd);
int		count_syntax(char *str);
char	*fix_syntax(char *str);
int		free_matrix(char **s);
//lnicoter
void	builtin_reader(char **command_line, t_data *shell_data, t_declaration *identity);
void	ft_echo(char **command_line);
void	ft_cd(char **command_line, t_data *shell_data);
void	ft_env(t_data *shell_data);
int		copy_env(char **env, t_data *mini_data);
void	ft_pwd();
void	update_oldpwd(t_data *shell_data);
void	update_pwd(t_data *shell_data);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_realloc(void *ptr, size_t size);
void	ft_export(char **command_line, t_data *shell_data, t_declaration *identity);
void	print_export(char **export_matrix);
void	sort_and_print_export(t_data *shell_data);
char	**setting_the_matrix(t_data *shell_data);
int		env_rows(t_data *shell_data);
int		put_arguments_in_list(t_declaration *identity, char *command_line);
void	insert_declaration(t_declaration **list, int concatenation, const char *name, const char *value);
void	print_list(t_declaration *list);
void	arguments_separation(char **command_line, int conc, t_declaration **identity);
void	add_env(t_data *shell_data, t_declaration **values);
void	super_strjoin(t_data *shell_data, t_declaration *values);
// void	insert_in_env(t_data shell_data, char *final_string, t_declaration *values);
// abuonomo
char			*expander(t_data *shell_data, char *input);
char			*translate_wild(t_data *shell_data, char *input);
int				is_wildcard(char *input);
char			**matrix_directory(t_data *shell_data);
char			*ft_strjoin_wild(char const *s1, char const *s2);
char			*get_extension(const char *filename);
int				ft_strcmp_env(const char *input, const char *env);
struct dirent	**matrix_file(t_data *shell_data);
void			stampaMatriceChar(char **matrice);
char			*current_dir(void);
char			*ft_strcpy(char *dest, char *src);
char			*launch_exp_wild(t_data *shell_data, char *input);
char			*ft_strncpy(char *dest, char *src, unsigned int n);
void			ft_strncat(char **dest, char c, int nb);
char			*ft_strcat(char *dest, char *src);
#endif
