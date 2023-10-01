# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lnicoter <lnicoter@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/04 19:18:35 by mlongo            #+#    #+#              #
#    Updated: 2023/09/29 17:32:05 by lnicoter         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
SRCS_DIR := ./
OBJS := ft_strlcpy.o ft_calloc.o ft_putnbr_fd.o ft_strdup.o ft_tolower.o \
	ft_strlcat.o ft_isprint.o ft_isdigit.o ft_memchr.o ft_substr.o \
	ft_putendl_fd.o ft_memcmp.o ft_strncmp.o ft_striteri.o ft_memset.o \
	ft_putchar_fd.o ft_split.o ft_strnstr.o ft_bzero.o ft_atoi.o ft_isalpha.o \
	ft_strjoin.o ft_memmove.o ft_isascii.o ft_strlen.o ft_strrchr.o \
	ft_toupper.o ft_isalnum.o ft_strmapi.o ft_strtrim.o ft_itoa.o ft_strchr.o \
	ft_memcpy.o ft_putstr_fd.o
	# ft_lstlast.o ft_lstiter.o ft_lstsize.o \
	# ft_lstadd_back.o ft_lstadd_front.o ft_lstclear.o ft_lstdelone.o \
	# ft_lstmap.o ft_lstnew.o ft_strcmp.o \
FLAGS := -Wall -Werror -Wextra

B_OBJS = ft_lstnew.o ft_lstadd_front.o ft_lstsize.o ft_lstlast.o ft_lstadd_back.o ft_lstdelone.o ft_lstclear.o ft_lstiter.o ft_lstmap.o

all: $(NAME)

%.o : %.c
	@gcc $(FLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@ar crs libft.a $(OBJS)

bonus : ${B_OBJS}
	@ar crs libft.a $(B_OBJS)

clean:
	@rm -f $(OBJS) ${B_OBJS}

fclean: clean
	@rm -f $(NAME)

re: fclean all
