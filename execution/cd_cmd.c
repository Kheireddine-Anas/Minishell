#include "../minishell.h"
#include <string.h>

char	*get_env(t_env *envs, char *srch)
{
	t_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (!(strcmp(tmp->variable, srch)))
		{
			return (tmp->value);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

void	cmd_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

void	cmd_cd(char **path, t_env *env)
{
	char	*pth;

	if(path[1])
	{
		if (chdir(path[1]) == -1) //Change the working directory if it not changed it print an error
		{
			printf("cd: No such file or directory %s", path[1]);
			exit(0);
		}
	}
	else
	{
		pth = get_env(env, "HOME"); // for cd command without args it change the working directory to HOME
		if (!pth)
		{
			printf("Set HOME env\n"); // if HOME var not exist
			exit(1);
		}
		else if (chdir(pth) == -1)
		{
			printf("cd: No such file or directorys %s", pth);
			exit(1); 
		}
	}
}
// void cd(t_cmd	*lst_cmd, char **envp)
// {
// 	int i  = 0;
// 	t_env	*env; //ENV struct
// 	t_env	*tmp1=NULL;

// 	env = set_env(envp[i++]);
// 	tmp1 = env;
// 	while (envp[i])
// 	{
// 		tmp1->next = set_env(envp[i]);
// 		tmp1 = tmp1->next;
// 		i++;
// 	}
// 	cmd_cd(lst_cmd->option,env);
// }

// int builtten(t_cmd	*lst_cmd, char **envp)
// {
// 	if(ft_strncmp("cd", lst_cmd->option[0], 2) == 0)
// 	{
// 			cd(lst_cmd, envp);
// 			return (1);
// 	}
// 	return(0);
// }