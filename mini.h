#ifndef MINI_H
#define MINI_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct s_env
{
	char			*variable;
	char			*value;
	struct s_env	*next;
}	t_env;

void	*ft_calloc(int count, int size);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);
char	*get_env(t_env *envs, char *srch);
void	cmd_cd(char **path, t_env *env);
void	cmd_pwd();

#endif