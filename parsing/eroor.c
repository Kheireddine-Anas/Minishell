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
void error_ch(char *str)
{
	printf("\033[1;34mminishell xas: %s : %s\033[0m\n", str, strerror(errno));
	exit(0);
}
int	filecommade(t_cmd *cmd, char **env)
{
	int		fd[2];

	if(!cmd->option && (cmd->in && cmd->in[0][0] == '<'  && cmd->in[0][1] != '<'))
		return(1);
	if(!cmd->option &&(cmd->out && cmd->out[0] == '>'  && cmd->out[1] != '<'))
		return(1);
	if (!cmd->option && *cmd->in && cmd->in[0][0] == '<' && cmd->in[0][1] == '<')
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
	else 

	if (cmd->option[0][0] == '\0')
		errer_cmd(cmd->option[0]);
	else if (cmd->option[0][0] == '/')
	{
		if(access(cmd->option[0], X_OK) != 0)
			errer_cmd(cmd->option[0]);
	}
	else if (cmd->option[0][0] == '.' && cmd->option[0][1] == '/')
	{
		if(access(cmd->option[0], X_OK))
			errer_cmd(cmd->option[0]);
	}
	else if (!get_path(env,cmd->option[0],0))
		errer_cmd(cmd->option[0]);
	return (0);
}
