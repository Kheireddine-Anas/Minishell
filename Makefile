src  =   main.c split_sing_quot.c split_doubl_quot.c
obj = $(src:.c=.o)
NAME = minishell
LIBFT = libftt_/libft.a

all:  $(NAME)

$(NAME): $(obj)
	$(MAKE) -C libftt_
	gcc -Wall -Wextra -Werror  -lreadline -o $(NAME) $(obj) $(LIBFT)

%.o: %.c getNextLine/get_next_line.h  mandatori/pipex.h bonus/pipex_bonus.h
	gcc -Wall -Wextra -Werror -c $< -o $@

clean:
	$(MAKE) -C libftt_ clean
	rm -rf $(obj) 

fclean : clean
	$(MAKE) -C libftt_ fclean
	rm -rf $(NAME) 

re : fclean all

bonus_re : fclean bonus

.PHONY : all clean