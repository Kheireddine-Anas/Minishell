#include "../minishell.h"

void error_alocation(void)
{
	perror("Allocation error");
	exit(EXIT_FAILURE);
}
static void errer_cmd(char *str)
{
	printf("\033[1;31mminishell : %s : %s\033[0m\n",str, strerror(errno));
	exit(127);
}
int	filecommade(t_cmd *cmd, char **env)
{
	int		fd[2];

	if(!cmd->cmd && ((cmd->in && cmd->in[0][0] == '<'  && cmd->in[0][1] != '<') || (cmd->out && cmd->out[0] == '>'  && cmd->out[1] != '<')))
		return(1);
	if (!cmd->cmd && *cmd->in && cmd->in[0][0] == '<' && cmd->in[0][1] == '<')
	{
		if (pipe(fd) == -1)
		{
			printf("error\n");
			exit(1);
		}
		here_doc(cmd, fd);
		close(fd[1]);
		close(fd[0]);
		return (1);
	}
	if (cmd->cmd[0] == '\0')
		errer_cmd(cmd->cmd);
	else if (cmd->cmd[0] == '/')
	{
		if(access(cmd->cmd, X_OK) != 0)
			errer_cmd(cmd->cmd);
	}
	else if (cmd->cmd[0] == '.' && cmd->cmd[1] == '/')
	{
		if(access(cmd->cmd, X_OK))
			errer_cmd(cmd->cmd);
	}
	else if (!get_path(env, cmd->cmd,0))
		errer_cmd(cmd->cmd);
	return (0);
}
