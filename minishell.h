#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/wait.h>
# include <fcntl.h>
#include <signal.h>

typedef struct env_s
{
	char	*key;
	char	*value;
	struct env_s	*next;
} env_t;

char	*get_path(char **envp, char *cmd, int i);
int		ft_strlen_2_erra(char **str);
void	whilloop(int *fd);
void	erro(void);
char	**split_command(const char *command);
void	execute(char *argv, char **envp);
void	commad_path(char *argv, char **envp);
void	wit_process(int argc, pid_t **pids,int fd0,int fd1);
void	lop_her_doc(int argc, char *argv[], char **envp, int *fd);
void	parent_process_her_doc(int argc, char **argv, char **envp);
void	run_script(char *script_path, char **envp);
void	errer_cmd(void);
void	filecommade(char **argv,int i);
void	malloc_erro(int *str);
char	**ft_split_pipe(char *s);
char	**splite_variable(char *s);
char **create_cmd(char **str);
char	*strjoi(char *s1, char *s2, char *s3);
env_t	*lstlast(env_t *lst);
void	add_back(env_t **lst, env_t *new);
int	lstsize(env_t *lst);
env_t *get_env(char **envp);
char	**realloc_cmd(char ***cmd, int *capacity);
char	**split_singl_qot(const char *command);
char **get_erray_env(env_t	*env);
char	**split_double_qot(const char *command, char **envp);
#endif