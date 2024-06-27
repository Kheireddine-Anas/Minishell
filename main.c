#include "minishell.h"
int main() {

    char *cmd_line;

	while(1)
	{
		cmd_line = readline("minishell-$");
		add_history(cmd_line);
		char **cmd = split_double_qot(cmd_line);
		int i = 0;
		while (cmd[i])
		{
			printf("cmd[%d] = %s\n", i, cmd[i]);
			i++;
		}
	}
    return (0);
}
