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
env_t *get_env(char **envp);
char	**split_singl_qot(const char *command);
char **get_erray_env(env_t	*env);
char	**split_double_qot(const char *command, char **envp);
#endif