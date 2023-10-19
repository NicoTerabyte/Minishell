/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:15:02 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/10/19 20:53:11 by lnicoter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

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
# include "../tokenizer/tokenizer.h"
# include "../libft/libft.h"
# include "../minishell.h"
# include "../lexer/lexer.h"
#include 	"../global.h"
# include "../lexer/lexer.h"
# include "../libft/libft.h"
# include "../tokenizer/tokenizer.h"
# include "../tree/tree.h"
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
	char			**export_env;
	// t_declaration	*identity;
	// t_declaration	*head;
} t_data;

// int		cmd_name(char *str);
// void	parser(char **splitcmd);
//int		count_syntax(char *str);
// char	*fix_syntax(char *str);
//int		free_matrix(char **s);
//lnicoter
void	ft_echo(char **command_line);
void	ft_cd(char **command_line); //prima ci stava anche shell_data ma non serve al momento grazie alla funzione env_container
void	ft_env(void);
char	**copy_env(char **env, char **env_copy);
void	ft_pwd(void);
void	update_oldpwd(void); //aggiornati perché env è gestita in maniera differente
void	update_pwd(void); //per info guardare funzione env_container
//int		ft_strcmp(const char *s1, const char *s2);
void	*ft_realloc(void *ptr, size_t size);
void	ft_export(t_declaration *node);
void	print_export(char **export_matrix);
void	sort_and_print_export(char **env);
char	**setting_the_matrix(char **env);
int		env_rows(char **env);
int		check_arguments_validation(char *command_line);
void	insert_declaration(t_data *shell_data, int concatenation, const char *name, const char *value);
void	print_list(t_declaration *list);
void	arguments_separation(t_data *shell_data, char **command_line, int conc);
void	add_export_env(char **env);
char	*super_strjoin(t_data *shell_data);
void	env_adding(char *final_string, char **env);
void	puppamelo(t_data *lnico);
int		check_doubles(t_declaration *node, char **env);
// void	change_if_needed(t_data *shell_data, int pos);
char	*i_hate_this_strcpy_for_apix(char *dst, char *src);
char	*ft_strjoin_damn_you_leaks(char *s1, char  *s2);
// void	ft_strcat(char	*dst, const char *src);
void	(t_declaration	*node, char **env);
int		check_if_good_for_env(t_declaration *node);
char	*ft_strndup(char *str, int start, int finish);
void	change_if_needed_env_ver(t_declaration *node, int pos, char **env);
void	concatenation_export(t_declaration *node, int pos, char **env);
char	**split_bt_nt_t_mc(char *str, char c);
void	phase1(t_data *shell_data, char **final_string);
void	phase2(char **final_string);
void	list_update(t_data *shell_data, int conc, char **com_line, int i);
void	updating(char	***separg);
void	overwrite(t_data *shell_data, int pos);
//unset
void	ft_unset(t_declaration *node);
void	copy_check_unset(char *str);
void	swap_mat(char **str1, char **str2);
//exit mlongo deve farci ancora qualcosa
int		ft_exit(char **args);
#endif
