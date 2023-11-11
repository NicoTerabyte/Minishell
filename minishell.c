/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:35:17 by fcarlucc          #+#    #+#             */
/*   Updated: 2023/11/11 12:28:58 by mlongo           ###   ########.fr       */
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
				splitcmd = ft_realloc(splitcmd, sizeof(char *), env_rows(splitcmd), env_rows(splitcmd) + env_rows(split_expanded));
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

int	main(int argc, char **argv, char **envp)
{
	char	*str;
	char	**splitcmd;
	char	*fixed;
	t_token	*token_list;
	t_tree	*tree;
	t_mini	*mini;

	(void)argc;
	(void)argv;
	mini = ft_calloc(1, sizeof(t_mini));
	copy_env(envp, mini);
	token_list = NULL;
	increment_shlvl(mini);
	while (1)
	{
		unlink_here_docs(handle_list_heredocs(LIST));
		handle_list_heredocs(START);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, signal_handler);
		signal(SIGTERM, signal_handler);
		str = readline("Minishell> ");
		if (str == NULL)
		{
			printf("\n");
			free(str);
			free_env(mini);
			exit(0);
		}
		add_history(str);
		fixed = fix_syntax(str);
		free(str);
		if (!check(fixed, mini))
		{
			free(fixed);
			if (g_last_exit_status_cmd == 130)
				continue ;
			ft_putstr_fd("Syntax error\n", 2);
			g_last_exit_status_cmd = 2;
			continue ;
		}
		splitcmd = ft_split(fixed, ' ');
		free(fixed);
		splitcmd = wildcard_split(splitcmd, mini);
		token_list = tokenizer(splitcmd, mini);
		if (token_list)
			while (token_list->next)
				token_list = token_list->next;
		tree = tree_create(token_list, OP);
		if (token_list)
			while (token_list->prev)
				token_list = token_list->prev;
		mini->splitcmd = splitcmd;
		var_container(token_list, tree, mini, SET);
		execute(tree, STDIN_FILENO, STDOUT_FILENO, mini);
		free_matrix(splitcmd);
		ft_free_all(token_list, tree);
	}
}
