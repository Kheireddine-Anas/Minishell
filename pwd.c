#include "mini.h"

void	cmd_pwd()
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	printf("%s\n", pwd);
	free(pwd);
}

// int	main()
// {
// 	cmd_pwd();
// }