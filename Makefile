src  =   main.c split_sing_quot.c split_doubl_quot.c get_env.c libft_fontion.c splite_variable.c pipex_util1_bonus.c  pipex_util2_bonus.c pipex_util3_bonus.c  spli_pip.c
obj = $(src:.c=.o)
NAME = minishell
LIBFT = libft/libft.a

all:  $(NAME)

$(NAME): $(obj)
	$(MAKE) -C libft
	gcc -Wall -Wextra -Werror  -lreadline  -fsanitize=address  -o $(NAME) $(obj) $(LIBFT)
%.o: %.c getNextLine/get_next_line.h  mandatori/pipex.h bonus/pipex_bonus.h
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -rf $(obj) 

fclean : clean
	$(MAKE) -C libft fclean
	rm -rf $(NAME) 

re : fclean all

bonus_re : fclean bonus

.PHONY : all clean