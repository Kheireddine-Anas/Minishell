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
#include <errno.h>


typedef struct s_cmd
{
	char	**option;
	char	**in;
	char	**out;
	char	**fil_in;
	char	**fil_out;
	char	**extra_arg;
	int		index;
	int		single;
	int		double_q;
	struct s_cmd	*next;
} t_cmd;

typedef struct s_fd_last
{
	int		fd_in;
	int		fd_out;
	int		fd0;
	int		fd1;
	int		STDIN;
	int		STDOUT;
	int		her_doc;
	int		retu_red;
} t_fd_;
typedef enum
{
    QUOTE_SINGLE ,//0
    QUOTE_DOUBLE,//1
    WORD,//2
    SPACE_c,//3
	IN,//4
	OUT,//5
	APPEND,//6
	HER_DOC,//7
	FILE_NAME,//8
	CMD,//9
	VARIABLE,//10
	OPTION,//11
	PIP ,//12
	FILE_IN,//13,
	LIM,
	FILE_OUT//14
} TokenType;
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	env_t;

typedef struct
{
    TokenType type;
    char *value;
} Token;
typedef struct s_status
{
	int status;
} t_status;
void	clo(int fd);
int		error_rederaction(t_cmd *cmd);
int		while_loop(t_cmd **cmd ,t_fd_ **fd_in_out);
int		rediraction(t_cmd	*lst_cmd, t_status **status,  t_fd_ **fd_in_out);
int		builting(t_cmd	*lst_cmd, env_t	**env, t_status **status,  t_fd_ **fd_in_out) ;
void	cmd_unset(env_t **env, char *var);
void	cmd_echo(char **args);
void	print_env(env_t *env);
void	cmd_export(env_t **env, char **add);
env_t	*get_env(char **envp);
void	cmd_cd(char **path, env_t **env, t_status **status);
char	**get_erray_env(env_t	*env);
Token	*tokenize(char *p, int *num_tokens);
void	parse(Token **tokens, int num_tokens, char **envp, t_status	**status);
void	error_ch(t_status **status);
int		filecommade(t_cmd *cmd, char **env, t_status **status);
char	*get_path(char **envp, char *cmd, int i);
Token	*realloc_cmd( Token **tokens, int *capacity);
void	out(char **p, Token **tokens, int *num_tokens);
void	in(char **p, Token **tokens, int *num_tokens);
void	word(char **p, Token **tokens, int *num_tokens);
void	quot(char **p, Token **tokens, int *num_tokens);
int		is_space(char c);
void	error_alocation(void);
char	*add_valu_variable(char *str, char **envp, t_status	**status);
char	*remove_single_qoute(char *str);
char	*remove_doubl_qoute(char *str);
char 	**create_cmmmand(char **str);
char 	*chercher_variable(char *str, char **envp);
void	here_doc(t_cmd *cmd);
void	erro(t_status **status);
void	exe_cmd(t_cmd *cmd, char **envp,  t_status **status);
void	handle_sigint(int sig);
int		child_process(t_cmd *cmd, char **envp, int *fd, t_fd_ **fd_in_out, t_status **status);
void	fin_commande(t_cmd *cmd, char **envp, t_status **status);
void 	close_file(t_fd_ *fd_in_out, int *fd);
void	lstclear(t_cmd **lst);
void	execute(t_cmd	*cmd, char **envp,  t_status **status);
void	commad_path(t_cmd *cmd, char **envp,  t_status **status);
int		lstsize(t_cmd *lst);
t_cmd	*lstlast(t_cmd *lst);
int 	chek_herdoc(char *str);
char	*get_path(char **envp, char *cmd, int i);
void 	creat_cmd(t_cmd	**lst, char *command, char **env, t_status	**status);
char	*strjoi(char *s1, char *s2, char *s3);
char	**split_variable(const char *str);
void	print_list(t_cmd *lst_cmd);
#endif