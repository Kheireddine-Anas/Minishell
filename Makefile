SRC  =   min.c
NAME = minishell
CFLAGS = -Wall -Wextra -Werror -I/Users/akheired/.brew/opt/readline/include -L/Users/akheired/.brew/opt/readline/lib -lreadline -lncurses

all:  $(NAME)

$(NAME): $(obj)
	$(CC) $(CFLAGS) -o $(NAME) $(SRC) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(NAME)

fclean : clean
	rm -rf $(NAME) 

re : fclean all