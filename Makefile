# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: salaoui <salaoui@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 10:47:56 by salaoui           #+#    #+#              #
#    Updated: 2024/09/08 13:50:11 by salaoui          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c libft_utils.c tokenize.c tokenize_utils.c

CC = cc
C_FLAGS = -Wall -Wextra -Werror -lreadline
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
