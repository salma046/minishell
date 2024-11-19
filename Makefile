#Colors:
RED = "\033[0;31m"
YELLOW = "\033[0;33m"
BLACK = "\033[0m"
MAGENTA= "\033[1;35m"
CYAN = "\033[36m"
GREEN0= "\033[32m"
GREEN1 = "\033[38;5;121m"

#Files:
SRC = 	parcing/dollar.c parcing/handle_quotes.c \
		parcing/nodes.c  parcing/parsing.c \
		parcing/nodes_utils.c parcing/dollar_utils.c \
		parcing/tokenize_utils.c parcing/tokenize.c \
		builtins/checking_cmd.c builtins/ft_cd.c \
		builtins/ft_echo.c builtins/ft_env.c \
		builtins/ft_pwd.c  builtins/ft_exit.c \
		builtins/ft_unset.c builtins/ft_export.c \
		redirections/heredoc.c redirections/input.c \
		redirections/output.c redirections/append.c \
		redirections/ft_redirections.c \
		utilss/libft_utils.c utilss/sjd_fun_utils.c \
		execution/execute_commands.c \
		minishell.c

OBJ = $(SRC:.c=.o)

#Flags:
CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address

#Library:
NAME = minishell
LIBFT = libft.a

all: $(NAME)

$(NAME)	: $(OBJ) $(LIBFT)
	@echo $(CYAN)Making minishell .. 👾"\033[0m"
	@$(CC)  $(OBJ) $(LIBFT)  $(CFLAGS) -lreadline -o $(NAME) 


$(LIBFT):
	@make -C libft
	@mv libft/libft.a .

clean: 
	@echo  $(GREEN0)Cleaning 🧹
	@rm -rf  $(OBJ) 
	@make -C  libft clean 
	@rm -rf  $(LIBFT)

fclean: clean
	@rm -rf  $(NAME) 
	@echo "\033[0;33mDone cleaning \033[0m"✨ 

re: fclean all

.PHONY: re clean fclean
