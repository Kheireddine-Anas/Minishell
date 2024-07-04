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
#include "libft/libft.h"


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
void	lstclear(t_cmd **lst);
void	run_script(t_cmd	*cmd, char **envp);
void	execute(t_cmd	*cmd, char **envp);
void	commad_path(t_cmd *cmd, char **envp);
int		lstsize(t_cmd *lst);
t_cmd	*lstlast(t_cmd *lst);
char 	**split_and_include_symbols(const char *str);
char	**realloc_cmd(char ***cmd, int *capacity);
char	**split_singl_qot(const char *command);
char	**ft_split_pipe(char *s);
char	**split_double_qot(const char *command, char **envp);
int 	chek_herdoc(char *str);
char	*get_path(char **envp, char *cmd, int i);
void 	creat_cmd(t_cmd	**lst, char **command, char **env);
char	*strjoi(char *s1, char *s2, char *s3);
char	**splite_variable(char *s);
#endif