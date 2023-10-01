/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/10/01 20:24:51 by lnicoter         ###   ########.fr       */
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
# include <time.h>
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

typedef struct s_declaration
{
	int						concatenation; //true o false
	char					*name; //nome della variabile da inserire nell'export
	char					*value; //il valore di quest'ultima
	struct	s_declaration	*next; //la variabile successiva
}	t_declaration;

typedef struct s_data
{
	char			*path;
	char			*old_path;
	char			**copy_env;
	char			**export_env;
	t_declaration	*identity;
} t_data;

int		cmd_name(char *str);
void	parser(char **splitcmd);
int		count_syntax(char *str);
char	*fix_syntax(char *str);
int		free_matrix(char **s);
//lnicoter
void	builtin_reader(char **command_line, t_data *shell_data);
void	ft_echo(char **command_line);
void	ft_cd(char **command_line, t_data *shell_data);
void	ft_env(t_data *shell_data);
int		copy_env(char **env, t_data *mini_data);
void	ft_pwd();
void	update_oldpwd(t_data *shell_data);
void	update_pwd(t_data *shell_data);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_realloc(void *ptr, size_t size);
void	ft_export(char **command_line, t_data *shell_data);
void	print_export(char **export_matrix);
void	sort_and_print_export(t_data *shell_data);
char	**setting_the_matrix(t_data *shell_data);
int		env_rows(t_data *shell_data);
int		check_arguments_validation(char *command_line);
void	insert_declaration(t_data *shell_data, int concatenation, const char *name, const char *value);
void	print_list(t_declaration *list);
void	arguments_separation(t_data *shell_data, char **command_line, int conc);
void	add_export_env(t_data *shell_data);
char	*super_strjoin(t_data *shell_data);
// void	insert_in_env(t_data shell_data, char *final_string, t_declaration *values);
void	init_structs(t_data **shell_data, char **envp);
void	env_adding(char *final_string, t_data *shell_data);
void	puppamelo(t_data *lnico);
int		check_doubles(t_data *shell_data);
void	change_if_needed(t_data *shelll_data, int pos);
char	*i_hate_this_strcpy_for_apix(char *dst, char *src);
char	*ft_strjoin_damn_you_leaks(char *s1, char  *s2);
void	ft_strcat(char	*dst, const char *src);
void	add_to_the_real_env(t_data *shell_data);
int		check_if_good_for_env(t_data *shell_data, int index);
char	*ft_strndup(char *str, int start, int finish);
void	change_if_needed_env_ver(t_data	*shell_data, int pos);
void	concatenation_export(t_data *shell_data, int pos);
void	ft_strcat(char *dst, const char *src);
#endif
