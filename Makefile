src  =   parssing.c split_pip.c main.c rediraction.c splite_qot.c split_variable.c sing_qot.c splite_bay_symbole.c run_cmd.c
obj = $(src:.c=.o)
NAME = minishell
LIBFT = libft/libft.a
CFLAG = -Wall -Wextra -Werror      -I/Users/ahamdi/.brew/opt/readline/include 
# -fsanitize=address 
LFLAG = -L/Users/ahamdi/.brew/opt/readline/lib   -lreadline -lncurses 

all:  $(NAME)

$(NAME): $(obj)
	make -C libft
	gcc   $(CFLAG) -o $(NAME) $(obj) $(LIBFT) $(LFLAG)

%.o: %.c
	cc $(CFLAG)  -c $< -o $@

clean:
	make -C libft clean
	rm -rf $(obj) 

fclean : clean
	make -C libft fclean
	rm -rf $(NAME) 

re : fclean all

bonus_re : fclean bonus

.PHONY : all clean