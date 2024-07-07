SRC  =   min.c ft_print.c utils.c
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -I/Users/akheired/.brew/opt/readline/include -L/Users/akheired/.brew/opt/readline/lib -lreadline -lncurses

# MINISHELL_ART = \
# "\033[32m\n"\
# "███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████ ╗██╗  ██╗ ███████╗ ██╗      ██╗     \n"\
# "████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════ ╝██║  ██║ ██╔════╝ ██║      ██║     \n"\
# "██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████ ╗███████║ █████╗   ██║      ██║     \n"\
# "██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██ ║██╔══██║ ██╔══╝   ██║      ██║     \n"\
# "██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████ ║██║  ██║ ███████╗ ███████╗ ███████╗\n"\
# "╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════ ╝╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n"\
# "						      By: AHAMDI && AKHEIRED    \033[0m\n"

all:  $(NAME)

$(NAME): $(obj)
	@echo $(MINISHELL_ART)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(NAME)

fclean : clean
	rm -rf $(NAME) 

re : fclean all	