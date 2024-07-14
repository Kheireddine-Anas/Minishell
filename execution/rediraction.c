#include "../minishell.h"

void	erro(t_status **status)
{
	perror("Error in open file");
	(*status)->status = 3;
}
void handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int	child_process(t_cmd *cmd, char **envp, int *fd, t_fd_ **fd_in_out,  t_status **status)
{

	if(error_rederaction(cmd) == 1)
		return (0);
	
	if (!cmd || !cmd->option || !envp)
	{
		perror("invalide command");
		(*status)->status = 1;
		return (0);
	}
	if(cmd->single > 0 || cmd->double_q > 0)
	{
		ft_putstr_fd("\033[1;31msyntax error : error in quot\033[0m\n", 2);
		(*status)->status = 1;
		return (0);
	}
	if( (*fd_in_out)->retu_red != 3)
	{
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
	}
	exe_cmd(cmd, envp, status);
	return (0);
}
void	fin_commande(t_cmd *cmd, char **envp, t_status **status)
{
	if (!cmd->option[0])
	{
		perror("invalide command");
		(*status)->status = 1;
		exit(1);
	}
	if (cmd->single > 0 || cmd->double_q > 0)
	{
		ft_putstr_fd("\033[1;31msyntax error : error in quot\033[0m\n", 2);
		(*status)->status = 1;
		exit(1);
	}
	exe_cmd(cmd, envp, status);
}

int chek_herdoc(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while(str[i] && str[i + 1])
	{
		if ((str[i] == '<' && str[i +1] == '<') || (str[i] == '>' && str[i +1] == '>'))
		return (1);
		i++;
	}
	return (0);
}
