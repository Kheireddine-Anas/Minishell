src  =  parsing/parssing.c   parsing/eroor.c main.c execution/execut_cmd.c parsing/util1_parsing.c parsing/split_variable.c parsing/spli_qot.c execution/run_cmd.c execution/her_doc.c getNextLine/get_next_line_utils_bonus.c  getNextLine/get_next_line_bonus.c parsing/util2_parsing.c execution/utul_cmd.c parsing/env_1.c execution/cd_cmd.c execution/export.c\
		parsing/builting.c execution/fonction_mian.c execution/echo.c parsing/util3_parsin.c parsing/util4_parsin.c parsing/util5_parsin.c parsing/wildcars.c parsing/wildcars_util.c parsing/rederaction.c parsing/builting_fork.c\
		execution/util_cd.c parsing/utul_env.c parsing/util_error.c parsing/fonction_linked_list.c parsing/free_focntion.c parsing/error_parsing.c\
		parsing/util2_add_to_neoud.c parsing/remouve_double_quot.c parsing/wildcars_util2.c parsing/leakser.c parsing/util3_add_tonoud.c utul_main.c
obj = $(src:.c=.o)  
NAME = minishell
LIBFT = libft/libft.a
CFLAG = -Wall -Wextra -Werror -I/Users/akheired/.brew/opt/readline/include 
LFLAG = -L/Users/akheired/.brew/opt/readline/lib  -lreadline -lncurses

MINISHELL_ART = \
"\033[32m\n"\
"███╗   ███╗ ██╗ ███╗   ██╗ ██╗ ███████ ╗██╗  ██╗ ███████╗ ██╗      ██╗     \n"\
"████╗ ████║ ██║ ████╗  ██║ ██║ ██╔════ ╝██║  ██║ ██╔════╝ ██║      ██║     \n"\
"██╔████╔██║ ██║ ██╔██╗ ██║ ██║ ███████ ╗███████║ █████╗   ██║      ██║     \n"\
"██║╚██╔╝██║ ██║ ██║╚██╗██║ ██║ ╚════██ ║██╔══██║ ██╔══╝   ██║      ██║     \n"\
"██║ ╚═╝ ██║ ██║ ██║ ╚████║ ██║ ███████ ║██║  ██║ ███████╗ ███████╗ ███████╗\n"\
"╚═╝     ╚═╝ ╚═╝ ╚═╝  ╚═══╝ ╚═╝ ╚══════ ╝╚═╝  ╚═╝ ╚══════╝ ╚══════╝ ╚══════╝\n"\
"						      By: AHAMDI && AKHEIRED    \033[0m\n"

$(NAME): ascii_art $(obj)
	make -C libft
	$(CC) $(CFLAG) -o $(NAME) $(obj) $(LIBFT) $(LFLAG)

all: $(NAME)

ascii_art:
	@echo $(MINISHELL_ART)

%.o: %.c
	$(CC) $(CFLAG) -c $< -o $@

clean:
	make -C libft clean
	rm -rf $(obj)

fclean : clean
	make -C libft fclean
	rm -rf $(NAME)

re : fclean all

bonus_re : fclean bonus

.PHONY : all clean
