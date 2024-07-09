#include "minishell.h"

void	whilloop(int *fd, t_cmd *cmd)
{
	// int fd0 = 0;
	(void)cmd;
	// if(cmd != NULL && cmd->in != NULL)
	// {
	// 	if(cmd->index != 0 &&ft_strncmp("<", *cmd->in, ft_strlen(*cmd->in)) == 0)
	// 	{
	// 		fd0 = open(*(cmd->extra_arg), O_RDONLY);
	// 		if (fd0 == -1)
	// 			erro();
	// 		dup2(fd0, STDIN_FILENO);
	// 	}
	// }
	// else 
	// {
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
	// }
}
void	wit_process(int argc, pid_t **pids,int fd0, int fd1)
{
	int	j;

	j = 0;
	while (j < argc)
	{
		waitpid((*pids)[j], NULL, 0);
		j++;
	}
	free(*pids);
	dup2(fd0, STDIN_FILENO);
	dup2(fd1, STDOUT_FILENO);
}

void cd(t_cmd	*lst_cmd, char **envp)
{
	int i  = 0;
	t_env	*env; //ENV struct
	t_env	*tmp1=NULL;

	env = set_env(envp[i++]);
	tmp1 = env;
	while (envp[i])
	{
		tmp1->next = set_env(envp[i]);
		tmp1 = tmp1->next;
		i++;
	}
	cmd_cd(lst_cmd->option,env);
}
static void	lop(t_cmd	*lst_cmd, char **envp)
{
	int		i = 0;
	int		fd[2];
	pid_t	*pids;
	t_cmd	 *last;
	t_cmd	 *tmp;
	int fd0;
	int fd1;
	t_fd_ch *fd_in_out;
	t_fd_last *fd_last;

	if(ft_strncmp("cd", lst_cmd->option[0], 2) == 0)
	{
			cd(lst_cmd, envp);
			return ;
	}
	fd0 = dup(STDIN_FILENO);
	fd1 = dup(STDOUT_FILENO);
	if(!lst_cmd || !envp)
		return ;
	last = lstlast(lst_cmd);
	pids = ft_calloc(lstsize(lst_cmd), sizeof(pid_t));
	tmp = lst_cmd;
	if (filecommade(last, envp) == 1)
		return ;
	while (lst_cmd)
	{
		if (pipe(fd) == -1)
		{
			printf("error\n");
			exit(1);
		}
		pids[i] = fork();
		if (pids[i] == 0 && lst_cmd != last)
			child_process(lst_cmd, envp, fd, &fd_in_out);
		else if (pids[i] == 0 && lst_cmd == last)
			fin_commande(lst_cmd, envp, &fd_last, fd0, fd1);
		lst_cmd = lst_cmd->next;
		// close( fd_in_out->fd0);
		// close( fd_in_out->fd1);
		whilloop(fd,lst_cmd);
	}
	wit_process(lstsize(tmp), &pids,fd0,fd1);
	close_file(fd0, fd1, fd, fd_last);
}
void close_file(int fd0,int fd1, int *fd, t_fd_last *fd_last)
{
	close(fd[0]);
	close(fd[1]);
	close(fd1);
	close(fd0);
	close(fd_last->fd0);
	close(fd_last->fd1);
}
int main (int argc, char *argv[], char **envp)
{
	char *line;
	t_cmd	*lst_cmd;
	// int i =0;
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	// env = get_erray_env(get_env(envp));
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	while(1)
	{
		line = readline("\033[1;32mminishell-$ \033[0m");
		if(line == NULL)
			break;
		add_history(line);
		creat_cmd(&lst_cmd, line, envp);
		// while(lst_cmd)
		// {	i = 0;
		// 	while(lst_cmd->option[i])
		// 	{
		// 		if(i == 0)
		// 			printf("command :%s\n",lst_cmd->option[i]);
		// 		else
		// 			printf("option :%s\n",lst_cmd->option[i]);
		// 		i++;;
		// 	}
		// 	i = 0;
		// 	while(lst_cmd->in[i])
		// 	{
		// 		printf("in :%s\n",lst_cmd->in[i]);
		// 		i++;
		// 	}
			
		// 	printf("out :%s\n",lst_cmd->out);
		// 	while((*lst_cmd->extra_arg))
		// 	{
		// 		printf("extra_arg :%s\n",(*lst_cmd->extra_arg));
		// 		lst_cmd->extra_arg++;
		// 	}
		// 	while((*lst_cmd->fil_out))
		// 	{
		// 		printf("file_out:%s\n",(*lst_cmd->fil_out));
		// 		lst_cmd->fil_out++;
		// 	}
		// 	while((*lst_cmd->fil_in))
		// 	{
		// 		printf("file_in:%s\n",(*lst_cmd->fil_in));
		// 		lst_cmd->fil_in++;
		// 	}
		// 	printf("*****************************************************************************\n");
		// 	lst_cmd = lst_cmd->next;
		// }
		lop(lst_cmd,envp);
		free(line);
		line = NULL;
		lstclear(&lst_cmd);
	}
}