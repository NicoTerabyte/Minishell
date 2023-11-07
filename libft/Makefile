# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abuonomo <abuonomo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 19:18:35 by mlongo            #+#    #+#              #
#    Updated: 2023/11/07 16:55:49 by abuonomo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
SRCS_DIR := ./

SRC = $(wildcard *.c)\

OBJ = $(SRC:.c=.o)

FLAGS := -Wall -Werror -Wextra

B_OBJS = ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o ft_lstdelone.o ft_lstclear.o ft_lstiter.o ft_lstmap.o

all: $(NAME)

%.o : %.c
	@gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJ)
	@ar crs libft.a $(OBJ)

bonus : ${B_OBJS}
	@ar crs libft.a $(B_OBJS)

clean:
	@rm -f $(OBJS) ${B_OBJS}

fclean: clean
	@rm -f $(NAME)

re: fclean all
