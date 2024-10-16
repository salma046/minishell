# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 10:47:56 by salaoui           #+#    #+#              #
#    Updated: 2024/10/12 11:44:05 by salaoui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c libft_utils.c tokenize.c tokenize_utils.c handle_quotes.c parsing.c \
	  dollar.c nodes_utils.c nodes.c

CC = cc
C_FLAGS = -Wall -Wextra -Werror -lreadline #-fsanitize=address
NAME = minishell

SRC_o := $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(SRC_o)
	$(CC) $(C_FLAGS) -o $(NAME) $(SRC_o)

clean:
	rm -f $(SRC_o)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY: $(SRC_o)
