# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/01 14:36:32 by fcarlucc          #+#    #+#              #
#    Updated: 2023/07/24 14:41:04 by lnicoter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c parser.c utils_libft.c \

OBJ = $(SRC:.c=.o)

FLAGS = -Wall -Werror -Wextra -g

#COLORS
RED = \033[1;31m

GREEN = \033[1;32m

YELLOW = \033[1;33m

DEFAULT = \033[0m

all :
	@$(CC) $(FLAGS) $(SRC) -o $(NAME) -lreadline
	@echo "$(GREEN)$(NAME) created!$(DEFAULT)"

clean:
	@rm -f $(OBJ)
	@echo "$(YELLOW)object files deleted!$(DEFAULT)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(RED)all deleted!$(DEFAULT)"

re: fclean all

.PHONY:			all clean fclean re
