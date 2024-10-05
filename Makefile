
#Colors:
RED = "\033[0;31m"
YELLOW = "\033[0;33m"
BLACK = "\033[0m"
MAGENTA= "\033[1;35m"
CYAN = "\033[36m"
GREEN0= "\033[32m"
GREEN1 = "\033[38;5;121m"

#Files:
SRC = 	ft_cd.c ft_echo.c dollar.c handle_quotes.c \
		libft_utils.c minishell.c nodes_utils.c parsing.c \
		sjd_fun_utils.c tokenize_utils.c tokenize.c \
		checking_cmd.c ft_pwd.c

OBJ = $(SRC:.c=.o)

#Flags:
CC = cc
CFLAGS = -Wall -Wextra -Werror

#Library:
NAME = minishell
LIBFT = libft.a

all: $(NAME)

$(NAME)	: $(OBJ) $(LIBFT)
	@$(CC)  $(OBJ) $(LIBFT)  $(CFLAGS) -lreadline -o $(NAME) 


$(LIBFT):
	@echo $(CYAN)Making libft .. 👾"\033[0m"
	@make -C libft
	@mv libft/libft.a .


clean: 
	@echo  $(GREEN0)Cleaning 🧹
	@rm -rf  $(OBJ) 
	@make -C  libft clean 
	@rm -rf  $(LIBFT)

fclean: clean
	@echo $(GREEN0)Full cleaning...
	@rm -rf  $(NAME) 
	@echo  $(YELLOW)Done cleaning ✨ 

re: fclean all

.PHONY: re clean fclean