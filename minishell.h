#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libft/libft.h"

typedef struct env_s
{
	char	*key;
	char	*value;
	struct env_s	*next;
} env_t;

typedef struct cmd_s
{
	char	*cmd;
	struct cmd_s	*next;
} cmd_t;
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