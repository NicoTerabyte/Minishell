# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlongo <mlongo@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/01 14:36:32 by fcarlucc          #+#    #+#              #
#    Updated: 2023/08/11 15:46:43 by mlongo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c ./tokenizer/tok_utils.c ./tokenizer/tok_utils_1.c ./tokenizer/tok_scan_1.c ./tokenizer/tok_list.c ./tokenizer/tokenizer.c \
		./tokenizer/tok_env_decl.c ./tokenizer/tok_redir.c ./tokenizer/tok_cmd.c ./gnl/get_next_line_bonus.c

OBJS = $(SRC:.c=.o)

FLAGS := -Wall -Werror -Wextra -g

LIBFT_PATH = ./libft

LIBFT = ${LIBFT_PATH}/libft.a

#COLORS
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

DEFAULT = \033[0m

all: $(NAME)

%.o : %.c
	@cc $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@make -C libft
	@make bonus -C libft
	@cc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@make clean -C libft
	@rm -f $(OBJS)
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "$(RED)all deleted!$(DEFAULT)"

re: clean fclean all
