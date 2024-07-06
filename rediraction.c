#include "minishell.h"

int chek_oune_qoute(char **str)
{
	int i ;

	i = 0;
	while(str[i])
	{
		if((str[i][0] == '\'' && str[i][ft_strlen(str[i] - 1)] != '\'' && str[i][ft_strlen(str[i] - 1)] != ' ') || (str[i][0] == '\"' && str[i][ft_strlen(str[i] - 1)] != '\"' && str[i][ft_strlen(str[i] - 1)] != ' '))
			return (1);
		i++;
	}
	return(0);
}
char	*strjoi(char *s1, char *s2, char *s3)
{
    int		size_total;
    char	*res;
    int		i;
    int		j;

    j = 0;
    i = 0;
    if (!s1 || !s2 || !s3)
	{
		if(!s1)
			return (ft_strjoin(s2, s3));
		if(!s2)
			return (ft_strjoin(s1, s3));
		if(!s3)
			return (ft_strjoin(s1, s2));
	}
    size_total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
    res = ft_calloc(size_total, 1);
    if (!res)
        return (NULL);
    while (s1[i] != '\0')
    {
        res[i] = s1[i];
        i++;
    }
    while (s2[j] != '\0')
        res[i++] = s2[j++];
    j = 0;
    while (s3[j] != '\0')
        res[i++] = s3[j++];
    res[i] = '\0';
    return (res);
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
	int fd1 = 0;
	int fd0;

	if(chek_oune_qoute(cmd->option) == 1)
	{
		ft_putstr_fd("error in quote\n", 2);
		exit(0);
	}
	if (!cmd->cmd)
	{
		perror("invalide command");
		exit(0);
	}
    if(ft_strncmp("<<",cmd->in,ft_strlen(cmd->in)) == 0)
    {
        while_loop(cmd, fd);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
    }
	else if(ft_strncmp("<",cmd->in,ft_strlen(cmd->in)) == 0)
	{
		fd0 = open(*(cmd->extra_arg), O_RDONLY);
		if (fd0 == -1)
			erro();
		dup2(fd0, STDIN_FILENO);
        (*fd_in_out)->fd0 = fd0;
	}
	if(ft_strncmp(">",cmd->out,ft_strlen(cmd->out)) == 0)
	{
		fd1 = open(*(cmd->extra_arg), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd1 == -1)
			erro();
			cmd->extra_arg++;
		dup2(fd1, STDOUT_FILENO);
         (*fd_in_out)->fd1 = fd1;
	}
	else if(ft_strncmp(">>",cmd->out,ft_strlen(cmd->out)) == 0)
	{
		fd1 = open(*(cmd->extra_arg), O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd1 == -1)
			erro();
		cmd->extra_arg++;
		dup2(fd1, STDOUT_FILENO);
        (*fd_in_out)->fd1 = fd1;
	}
	else
		dup2(fd[1], STDOUT_FILENO);
	close(fd[0]);
	if (cmd->cmd[0] == '/')
		commad_path(cmd, envp);
	else if (cmd->cmd[0] == '.' && (cmd->cmd[1] == '/'))
		run_script(cmd, envp);
	else
		execute(cmd, envp);
	if (fd1 != 0)
		close(fd1);	
}
void	fin_commande(t_cmd *cmd, char **envp, t_fd_last **fd_last, int *fd, int fd0, int fd1)
{
	(void)fd0;
	(void)fd1;
	if(chek_oune_qoute(cmd->option) == 1)
	{
		ft_putstr_fd("error in quote\n", 2);
		exit(1);
	}
	if(cmd->index == 0 && ft_strncmp("<<",cmd->in,ft_strlen(cmd->in)) == 0)
    {
        while_loop(cmd, fd);
        dup2(fd[0], STDIN_FILENO);
        close(fd[1]);
    }
    else if(cmd->index != 0 && ft_strncmp("<<",cmd->in,ft_strlen(cmd->in)) == 0)
    {
		dup2(fd0,STDIN_FILENO);
        here_doc(cmd, fd, fd0);
        dup2(fd0, STDIN_FILENO);
        close(fd[1]);
    }
	if (cmd->index == 0 && ft_strncmp("<",cmd->in,ft_strlen(cmd->in)) == 0)
	{
		(*fd_last)->fd0 = open(*(cmd->extra_arg), O_RDONLY);
		if ((*fd_last)->fd0 == -1)
			erro();
		dup2((*fd_last)->fd0, STDIN_FILENO);
	}
	if (ft_strncmp(">",cmd->out,ft_strlen(cmd->out)) == 0)
	{
		(*fd_last)->fd1 = open(*(cmd->extra_arg), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if ((*fd_last)->fd1 == -1)
			erro();
		cmd->extra_arg++;
		dup2((*fd_last)->fd1, STDOUT_FILENO);
	}
	else if(ft_strncmp(">>",cmd->out,ft_strlen(cmd->out)) == 0)
	{
		(*fd_last)->fd1 = open(*(cmd->extra_arg), O_WRONLY | O_CREAT | O_APPEND, 0644);
		if ((*fd_last)->fd1 == -1)
			erro();
		dup2((*fd_last)->fd1, STDOUT_FILENO);
		cmd->extra_arg++;
	}
	if (cmd->cmd[0] == '/')
		commad_path(cmd, envp);
	else if (cmd->cmd[0] == '.' && cmd->cmd[1] == '/')
		run_script(cmd, envp);
	else
		execute(cmd, envp);
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
