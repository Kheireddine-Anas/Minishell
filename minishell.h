#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <stdbool.h>
#include "getNextLine/get_next_line_bonus.h"


typedef struct env_s
{
	char	*key;
	char	*value;
	struct env_s	*next;
} env_t;
typedef struct s_cmd
{
	char	*cmd;
	char	**option;
	char	*in;
	char	*out;
	char	**extra_arg;
	int		index;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_fd_last
{
	int		fd0;
	int		fd1;
} t_fd_last;
typedef struct s_fd
{
	int		fd0;
	int		fd1;
} t_fd_ch;
typedef enum
{
    QUOTE_SINGLE,
    QUOTE_DOUBLE,
    WORD,
    SPACE,
	IN,
	OUT,
	APPEND,
	HER_DOC,
	FILE_NAME
} TokenType;

typedef struct
{
    TokenType type;
    char *value;
} Token;
char	*add_valu_variable(char *str, char **envp);
char	*remove_single_qoute(char *str);
char	*remove_doubl_qoute(char *str);
char 	**create_cmmmand(char **str);
char 	*chercher_variable(char *str, char **envp);
int 	chek_oune_qoute(char **str);
char	**split_qot(const char *command, char **envp);
void 	here_doc(t_cmd *cmd, int *fd,int f);
void	erro(void);
void	while_loop(t_cmd *cmd, int *fd);
void	handle_sigint(int sig);
void	child_process(t_cmd *cmd, char **envp, int *fd, t_fd_ch **fd_in_out);
void	fin_commande(t_cmd *cmd, char **envp, t_fd_last **fd_last, int *fd, int fd0, int fd1);
void 	close_file(int fd0,int fd1, int *fd, t_fd_last *fd_last);
void	lstclear(t_cmd **lst);
void	run_script(t_cmd	*cmd, char **envp);
void	execute(t_cmd	*cmd, char **envp);
void	commad_path(t_cmd *cmd, char **envp);
int		lstsize(t_cmd *lst);
t_cmd	*lstlast(t_cmd *lst);
char 	**split_and_include_symbols(const char *str);
char	**realloc_cmd(char ***cmd, int *capacity);
char	**ft_split_pipe(char *s);
int 	chek_herdoc(char *str);
char	*get_path(char **envp, char *cmd, int i);
void 	creat_cmd(t_cmd	**lst, char **command, char **env);
char	*strjoi(char *s1, char *s2, char *s3);
char **split_variable(const char *str);
#endif