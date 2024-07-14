#include "../minishell.h"
#include <string.h>

static char	*get_valus(env_t *envs, char *srch)
{
	env_t	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (!(strcmp(tmp->key, srch)))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*cmd_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	return (pwd);
}

void	update_env(env_t **env, char *var, char *value)
{
	env_t *tmp;
	
	tmp = *env;
	while (tmp)
	{
		if (strcmp(tmp->key, var) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}
void	cmd_cd(char **path, env_t **env, t_status **status)
{
	char	*pth;
	char	*crnt;

	crnt = getcwd(NULL, 0);
	if(path[1])
	{
		if (path[1][0] == '-') //Change the working directory if it not changed it print an error
		{
			printf("cd: No doesn't accept options");
			// exit(1);
		}
		if (chdir(path[1]) == -1)
		{
			printf("cd: No such file or directory %s\n", path[1]);
			(*status)->status = 1;
		}
	}
	else
	{
		pth = get_valus(*env, "HOME");
		if (!pth)
		{
			ft_putstr_fd("Set HOME env\n", 2);
			(*status)->status = 1;
		}
		else if (chdir(pth) == -1)
		{
			printf("cd: No such file or directorys %s\n", pth);
			(*status)->status = 1;
		}		 
	}
	update_env(env, "PWD", cmd_pwd()); //UPDATE PWD 
	update_env(env, "OLDPWD", crnt);  //UPDATE OLDPWD
}

void	cmd_unset(env_t **env, char *var)
{
	env_t	*tmp;
	env_t	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (strcmp(tmp->key, var) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
void	cmd_echo(char **args)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		newline = 0;
		i = 2;
	}

	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1]) {
			printf(" ");
		}
		i++;
	}
	if (newline)
		printf("\n");
}