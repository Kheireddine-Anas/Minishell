src  =   main.c split_sing_quot.c split_doubl_quot.c get_env.c libft_fontion.c splite_variable.c pipex_util1_bonus.c  pipex_util2_bonus.c pipex_util3_bonus.c  spli_pip.c
obj = $(src:.c=.o)
NAME = minishell
LIBFT = libft/libft.a
CFLAG = -Wall -Wextra -Werror    -fsanitize=address   -I/Users/ahamdi/.brew/opt/readline/include  
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