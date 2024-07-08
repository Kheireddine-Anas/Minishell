#include "../minishell.h"

void exe_cmd(t_cmd *cmd, char **envp)
{
	if (cmd->cmd[0] == '/')
		commad_path(cmd, envp);
	else if (cmd->cmd[0] == '.' && cmd->cmd[1] == '/')
		run_script(cmd, envp);
	else
		execute(cmd, envp);
}