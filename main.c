#include "minishell.h"

void	whilloop(int *fd)
{
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
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

void clo(int fd)
{
	if(fd > 0)
		close(fd);
}
static void	lop(t_cmd	*lst_cmd, env_t	**env, t_status	**status , char *line)
{
	int		i = 0;
	int		fd[2];
	pid_t	*pids;
	t_cmd	 *last;
	t_cmd	 *tmp;
	t_fd_ *fd_in_out;
	char **envp;

	fd_in_out = ft_calloc(1, sizeof(t_fd_));
	fd_in_out->fd0 = 0;
	fd_in_out->fd1 = 0;
	fd_in_out->STDIN = 0;
	fd_in_out->STDOUT = 0;
	fd_in_out->her_doc = 0;
	envp = get_erray_env(*env);
	creat_cmd(&lst_cmd, line, envp, status);
	// print_list(lst_cmd);
	if (!lst_cmd)
	{
		(*status)->status = 1;
		return ;
	}
	fd_in_out->fd_in = dup(STDIN_FILENO);
	fd_in_out->fd_out = dup(STDOUT_FILENO);
	last = lstlast(lst_cmd);
	if((*lst_cmd->option) && builting(last, env, status, &fd_in_out) == 1)
	{
		close_file(fd_in_out, fd);
		return ;
	}
	if(!lst_cmd || !envp)
		return ;
	pids = ft_calloc(lstsize(lst_cmd), sizeof(pid_t));
	tmp = lst_cmd;
	if (filecommade(last, envp, status) == 1)
		return ;
	while (lst_cmd)
	{
		fd_in_out->retu_red = rediraction(lst_cmd, status, &fd_in_out);
		if (fd_in_out->retu_red == 2)
			break;
		if (pipe(fd) == -1)
		{
			ft_putstr_fd("error\n", 2);
			(*status)->status = 1;
			return ;
		}
		pids[i] = fork();
		if (pids[i] == 0 && lst_cmd != last)
			child_process(lst_cmd, envp, fd, &fd_in_out,  status);
		else if (pids[i] == 0 && lst_cmd == last)
			fin_commande(lst_cmd, envp, status);
		(*status)->status = 0;
		lst_cmd = lst_cmd->next; 
		whilloop(fd);
	}
	wit_process(lstsize(tmp), &pids,fd_in_out->fd_in,fd_in_out->fd_out);
	close_file(fd_in_out, fd);
}
void close_file(t_fd_ *fd_in_out, int *fd)
{
	clo(fd_in_out->fd_out);
	clo(fd_in_out->her_doc);
	clo(fd[0]);
	clo(fd[1]);
	clo(fd_in_out->fd0);
	clo(fd_in_out->fd1);
	clo(fd_in_out->STDIN);
	clo(fd_in_out->STDOUT);
	clo(fd_in_out->fd_in);
	
}
int main (int argc, char *argv[], char **envp)
{
	char		*line;
	t_status	*status;
	t_cmd		*lst_cmd;
	env_t		*envp_new;
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	envp_new = get_env(envp);
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	status = ft_calloc(1, sizeof(t_status));
	if (!status)
		return (0);
	status->status = 0;
	print_minishell();
	while(1)
	{
		line = readline("\033[1;32mmini-shell> \033[0m");
		if(line == NULL)
			break;
		add_history(line);
		lop(lst_cmd, &envp_new, &status, line);
		free(line);
		line = NULL;
		lstclear(&lst_cmd);
	}
}

void print_list(t_cmd *lst_cmd)
{
	int i ;
	
	while(lst_cmd)
		{	i = 0;
			while(lst_cmd->option[i])
			{
				if(i == 0)
					printf("command :%s\n",lst_cmd->option[i]);
				else
					printf("option :%s\n",lst_cmd->option[i]);
				i++;;
			}
			i = 0;
			while(lst_cmd->in[i])
			{
				printf("in :%s\n",lst_cmd->in[i]);
				i++;
			}
			i = 0;
			while(lst_cmd->out[i])
			{
				printf("out :%s\n",lst_cmd->out[i]);
				i++;
			}
			while((*lst_cmd->extra_arg))
			{
				printf("extra_arg :%s\n",(*lst_cmd->extra_arg));
				lst_cmd->extra_arg++;
			}
			while((*lst_cmd->fil_out))
			{
				printf("file_out:%s\n",(*lst_cmd->fil_out));
				lst_cmd->fil_out++;
			}
			while((*lst_cmd->fil_in))
			{
				printf("file_in:%s\n",(*lst_cmd->fil_in));
				lst_cmd->fil_in++;
			}
			printf("*****************************************************************************\n");
			lst_cmd = lst_cmd->next;
		}
}