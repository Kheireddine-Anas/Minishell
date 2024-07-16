src  =  parsing/parssing.c   parsing/eroor.c main.c execution/rediraction.c parsing/util1_parsing.c parsing/split_variable.c parsing/spli_qot.c execution/run_cmd.c execution/her_doc.c getNextLine/get_next_line_utils_bonus.c  getNextLine/get_next_line_bonus.c parsing/util2_parsing.c execution/utul_rederaction.c parsing/env_1.c execution/cd_cmd.c execution/export.c\
		parsing/builting.c
obj = $(src:.c=.o) 
NAME = minishell
LIBFT = libft/libft.a
CFLAG = -Wall -Wextra -Werror   -I/Users/ahamdi/.brew/opt/readline/include 
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