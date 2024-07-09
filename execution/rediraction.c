#include "../minishell.h"

int chek_oune_qoute(char **str)
{
	int i ;

	i = 0;
	while(str[i])
	{
		if((str[i][0] == '\'' && str[i][ft_strlen(str[i] - 1)] != '\'' && str[i][ft_strlen(str[i] - 1)] != ' ') 
				|| (str[i][0] == '\"' && str[i][ft_strlen(str[i] - 1)] != '\"' && str[i][ft_strlen(str[i] - 1)] != ' '))
			return (1);
		i++;
	}
	return(0);
}

void	erro(void)
{
	perror("Error in open file");
	exit(3);
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


void	child_process(t_cmd *cmd, char **envp, int *fd, t_fd_ch **fd_in_out)
{

	if (!(*cmd->option))
	{
		perror("invalide command");
		exit(0);
	}
	if(cmd->single > 0 || cmd->double_q > 0)
	{
		printf("\033[1;31msyntax error : error in quot\033[0m\n");
		exit(1);
	}
	else if(ft_strncmp("<", *cmd->in, ft_strlen(*cmd->in)) == 0)
	{
		(*fd_in_out)->fd0 = open(*(cmd->extra_arg), O_RDONLY);
		if ((*fd_in_out)->fd0 == -1)
			erro();
		dup2((*fd_in_out)->fd0, STDIN_FILENO);
	}
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	exe_cmd(cmd, envp);
}
void	fin_commande(t_cmd *cmd, char **envp, t_fd_last **fd_last, int fd0, int fd1)
{
	(void)fd0;
	(void)fd_last;
	(void)fd1;
	if (!(cmd->option))
	{
		perror("invalide command");
		exit(0);
	}
	if (cmd->single > 0 || cmd->double_q > 0)
	{
		printf("\033[1;31msyntax error : error in quot\033[0m\n");
		exit(1);
	}

	if (*cmd->fil_in)
	{
		while(*cmd->fil_in)
			cmd->fil_in++;
		cmd->fil_in--;
		(*fd_last)->fd1 = open(*cmd->fil_in, O_RDONLY );
		if ((*fd_last)->fd0 == -1)
			erro();
		dup2((*fd_last)->fd0, STDIN_FILENO);
	}
	if (*cmd->fil_out)
	{
		while(*cmd->fil_out)
		{	(*fd_last)->fd1 = open(*cmd->fil_out, O_CREAT | O_RDWR, 0777);;
			if ((*fd_last)->fd1 == -1)
				erro();
			close((*fd_last)->fd1);
			cmd->fil_out++;
		}
		cmd->fil_out--;
		(*fd_last)->fd1 = open(*cmd->fil_out, O_CREAT | O_RDWR, 0777);;
		if ((*fd_last)->fd1 == -1)
			erro();
		dup2((*fd_last)->fd1, STDOUT_FILENO);
	}
	exe_cmd(cmd, envp);
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
