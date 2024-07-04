#include "minishell.h"
void	erro(void)
{
	perror("Error in pipe or process");
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
void	whilloop(int *fd, t_cmd *cmd)
{
	int fd0 = 0;

	if(cmd != NULL && cmd->in != NULL)
	{
		if(ft_strncmp("<",cmd->in,ft_strlen(cmd->in)) == 0)
		{
			fd0 = open(*(cmd->extra_arg), O_RDONLY);
			if (fd0 == -1)
				erro();
			dup2(fd0, STDIN_FILENO);
		}
	}
	else
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
	}
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
static void	child_process(t_cmd *cmd, char **envp, int *fd)
{
	int fd1 = 0;
	int fd0;

	if (!cmd->cmd)
	{
		perror("invalide command");
		exit(0);
	}
	if(cmd->index == 0 && ft_strncmp("<",cmd->in,ft_strlen(cmd->in)) == 0)
	{
		fd0 = open(*(cmd->extra_arg), O_RDONLY);
		if (fd0 == -1)
			erro();
		dup2(fd0, STDIN_FILENO);
	}
	if(ft_strncmp(">",cmd->out,ft_strlen(cmd->out)) == 0)
	{
		fd1 = open(*(cmd->extra_arg), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd1 == -1)
			erro();
			cmd->extra_arg++;
		dup2(fd1, STDOUT_FILENO);
	}
	else if(ft_strncmp(">>",cmd->out,ft_strlen(cmd->out)) == 0)
	{
		fd1 = open(*(cmd->extra_arg), O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd1 == -1)
			erro();
		cmd->extra_arg++;
		dup2(fd1, STDOUT_FILENO);
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
	// close(fd0);
	// close(fd1);
}
static void	fin_commande(t_cmd *cmd, char **envp)
{
	int fd;
	int fd0;

	if(cmd->index == 0 && ft_strncmp("<",cmd->in,ft_strlen(cmd->in)) == 0)
	{
		fd0 = open(*(cmd->extra_arg), O_RDONLY);
		if (fd0 == -1)
			erro();
		dup2(fd0, STDIN_FILENO);
	}
	if(ft_strncmp(">",cmd->out,ft_strlen(cmd->out)) == 0)
	{
		fd = open(*(cmd->extra_arg), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			erro();
			cmd->extra_arg++;
		dup2(fd, STDOUT_FILENO);
	}
	else if(ft_strncmp(">>",cmd->out,ft_strlen(cmd->out)) == 0)
	{
		fd = open(*(cmd->extra_arg), O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			erro();
		dup2(fd, STDOUT_FILENO);
		cmd->extra_arg++;
	}
	if (cmd->cmd[0] == '/')
	{
		printf("***\n");
		commad_path(cmd, envp);
	}
	else if (cmd->cmd[0] == '.' && cmd->cmd[1] == '/')
		run_script(cmd, envp);
	else
		execute(cmd, envp);
}
static void	lop(t_cmd	*lst_cmd, char **envp)
{
	int		i;
	int		fd[2];
	pid_t	*pids;
	t_cmd	 *last;
	t_cmd	 *tmp;
	int fd0;
	int fd1;

	fd0 = dup(STDIN_FILENO);
	fd1 = dup(STDOUT_FILENO);
	if(!lst_cmd || !envp)
		return ;
	last = lstlast(lst_cmd);
	pids = ft_calloc(lstsize(lst_cmd), sizeof(pid_t));
	i = 0;
	tmp = lst_cmd;
	while (lst_cmd)
	{
		// filecommade(last);
		if (pipe(fd) == -1)
		{
			printf("error\n");
			exit(1);
		}
		pids[i] = fork();
		if (pids[i] == 0 && lst_cmd != last)
			child_process(lst_cmd, envp, fd);
		else if (pids[i] == 0 && lst_cmd == last)
			fin_commande(lst_cmd, envp);
		lst_cmd = lst_cmd->next;
		whilloop(fd,lst_cmd);
	}
	wit_process(lstsize(tmp), &pids,fd0,fd1);
	close(fd[0]);
	close(fd[1]);
}
int main (int argc, char *argv[], char **envp)
{
	char *line;
	char **split_pip;
	t_cmd	*lst_cmd;
	// char	**env;

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
		line = readline("minishell-$ ");
		if(line == NULL)
			break;
		add_history(line);
		split_pip = ft_split_pipe(line);
		creat_cmd(&lst_cmd, split_pip, envp);
		lop(lst_cmd,envp);
		free(line);
		line = NULL;
		lstclear(&lst_cmd);
	}
}