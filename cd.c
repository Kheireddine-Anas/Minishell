#include "minishell.h"

void	update_env(t_env *env, char *var, char *value)
{
	t_env *tmp;
	
	tmp = env;
	while (tmp)
	{
		if (ft_strcmp(tmp->variable, var) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}
void	cmd_cd(char **path, t_env *env)
{
	char	*pth;
	char	*crnt;

	crnt = getcwd(NULL, 0);
	if(path[1])
	{
		if (chdir(path[1]) == -1) //Change the working directory if it not changed it print an error
		{
			printf("cd: No such file or directory %s", path[1]);
			// exit(1);
		}
	}
	else
	{
		pth = get_env(env, "HOME"); // for cd command without args it change the working directory to HOME
		if (!pth)
		{
			printf("Set HOME env\n"); // if HOME var not exist
			// exit(1);
		}
		else if (chdir(pth) == -1)
		{
			printf("cd: No such file or directorys %s", pth);
			// exit(1); 
		}
	}
	update_env(env, "PWD", cmd_pwd()); //UPDATE PWD 
	update_env(env, "OLDPWD", crnt);  //UPDATE OLDPWD
	// cmd_pwd(); // See if the location is changed or not
}
