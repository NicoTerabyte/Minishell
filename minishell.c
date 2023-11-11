/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/11 13:39:58 by mlongo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_last_exit_status_cmd = 0;

char	**wildcard_split(char **splitcmd, t_mini *mini)
{
	int		i;
	int		j;
	char	*tmp;
	char	*expanded;
	char	**split_expanded;
	int		end;
	int		end_new;

	i = 0;
	j = 0;
	while (splitcmd[i])
	{
		expanded = ft_wildcard(splitcmd[i], mini);
		split_expanded = ft_split(expanded, ' ');
		if (split_expanded[1])
		{
			if (i != 0 && ft_isredirection(splitcmd[i - 1]))
			{
				free_matrix(split_expanded);
				splitcmd[i] = expanded;
			}
			else
			{
				end = env_rows(splitcmd) - 1;
				splitcmd = ft_realloc(splitcmd, sizeof(char *),
					env_rows(splitcmd), env_rows(splitcmd) + env_rows(split_expanded));
				end_new = env_rows(splitcmd) + env_rows(split_expanded) - 3 - i;
				while (end > i)
					splitcmd[end--] = splitcmd[end_new--];
				tmp = splitcmd[i];
				while (split_expanded[j])
					splitcmd[i++] = split_expanded[j++];
				free(expanded);
				free(split_expanded);
			}
		}
		else
		{
			free_matrix(split_expanded);
			splitcmd[i] = expanded;
		}
		if (splitcmd[i])
			i++;
	}
	return (splitcmd);
}

void	initializing_mini()
{
	unlink_here_docs(handle_list_heredocs(LIST));
	handle_list_heredocs(START);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);
}

void	ctrl_d_case(char *str, t_mini *mini)
{
	printf("\n");
	free(str);
	free_env(mini);
	exit(0);
}

void	parse_and_execute_mini(char **splitcmd, char *fixed, t_mini *mini)
{
	splitcmd = ft_split(fixed, ' ');
	free(fixed);
	splitcmd = wildcard_split(splitcmd, mini);
	mini->token_list = tokenizer(splitcmd, mini);
	if (mini->token_list)
		while (mini->token_list->next)
			mini->token_list = mini->token_list->next;
	mini->tree = tree_create(mini->token_list, OP);
	if (mini->token_list)
		while (mini->token_list->prev)
			mini->token_list = mini->token_list->prev;
	mini->splitcmd = splitcmd;
	var_container(mini->token_list, mini->tree, mini, SET);
	execute(mini->tree, STDIN_FILENO, STDOUT_FILENO, mini);
	free_matrix(splitcmd);
	ft_free_all(mini->token_list, mini->tree);
}

void	syntax_error(char *fixed)
{
	free(fixed);
	if (g_last_exit_status_cmd != 130)
	{
		ft_putstr_fd("Syntax error\n", 2);
		g_last_exit_status_cmd = 2;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**splitcmd;
	char	*fixed;
	t_mini	*mini;

	(void)argc;
	(void)argv;
	mini = ft_calloc(1, sizeof(t_mini));
	copy_env(envp, mini);
	mini->token_list = NULL;
	increment_shlvl(mini);
	while (1)
	{
		initializing_mini();
		str = readline("Minishell> ");
		if (str == NULL)
			ctrl_d_case(str, mini);
		add_history(str);
		fixed = fix_syntax(str);
		free(str);
		if (check(fixed, mini))
			parse_and_execute_mini(splitcmd, fixed, mini);
		else
			syntax_error(fixed);
	}
}
