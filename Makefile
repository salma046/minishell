# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saait-si <saait-si@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/30 10:47:56 by salaoui           #+#    #+#              #
#    Updated: 2024/09/19 05:18:16 by saait-si         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = minishell.c libft_utils.c tokenize.c tokenize_utils.c handle_quotes.c parsing.c ft_cd.c
CC = cc
C_FLAGS = -Wall -Wextra -Werror -lreadline
NAME = minishell

SRC_o := $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(SRC_o)
	@echo "Making $(NAME)"
	$(CC) $(C_FLAGS) -o $(NAME) $(SRC_o)

clean:
	rm -f $(SRC_o)

fclean: clean
	rm -f $(NAME)

re: fclean all

.SECONDARY: $(SRC_o)
