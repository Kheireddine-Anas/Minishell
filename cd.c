#include "mini.h"

void	cmd_cd(char **path, t_env *env)
{
	char	*pth;

	if(path[1])
	{
		if (chdir(path[1]) == -1) //Change the working directory if it not changed it print an error
		{
			printf("cd: No such file or directoryw %s", path[1]);
			exit(1);
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
	cmd_pwd(); // See if the location is changed or not
}
