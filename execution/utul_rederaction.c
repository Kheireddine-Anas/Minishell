#include "../minishell.h"

void	exe_cmd(t_cmd *cmd, char **envp, t_status **status)
{
	(*status)->status = 0;
	if (cmd->option[0][0] == '/')
		commad_path(cmd, envp, status);
	else if (cmd->option[0][0] == '.' && cmd->option[0][1] == '/')
	{
		if (execve(cmd->option[0], cmd->option, envp) == -1)
			error_ch( status);
	}
	else
		execute(cmd, envp, status);
}