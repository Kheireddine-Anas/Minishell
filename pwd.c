#include "minishell.h"

char	*cmd_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	return (pwd);
}