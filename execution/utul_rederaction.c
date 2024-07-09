#include "../minishell.h"

void exe_cmd(t_cmd *cmd, char **envp)
{
	if (cmd->option[0][0] == '/')
		commad_path(cmd, envp);
	else if (cmd->option[0][0] == '.' && cmd->option[0][1] == '/')
	{
		if (execve(cmd->option[0], cmd->option, envp) == -1)
			error_ch(cmd->option[0]);
	}
	else
		execute(cmd, envp);
}