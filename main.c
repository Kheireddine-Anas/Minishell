#include "minishell.h"
void ft_leaks(void)
{
	system("leaks minishell");
}
int	main(int argc, char **argv, char **envp)
{
    char *cmd_line;
	char **cmd;
	char **env;

	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	env = get_erray_env(get_env(envp));
	
	while (1)
	{
		cmd_line = readline("minishell-$");
		add_history(cmd_line);
		cmd = split_double_qot(cmd_line, envp);
		int i = 0;
		while (cmd[i])
		{
			printf("cmd[%d] = %s\n", i, cmd[i]);
			i++;
		}
	}
    return (0);
}

