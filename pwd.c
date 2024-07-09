#include "minishell.h"

char	*cmd_pwd(int val)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (val)
		printf("%s\n", pwd);
	return (pwd);
}