#include "minishell.h"

static void	child_process(char **argv, char **envp, int *fd, int i)
{
	if (argv[i][0] == '\0')
	{
		perror("invalide command");
		exit(0);
	}
	dup2(fd[1], STDOUT_FILENO);
	if (argv[i][0] == '/')
		commad_path(argv[i], envp);
	else if (argv[i][0] == '.' && (argv[i][1] == '/'))
		run_script(argv[i], envp);
	else
		execute(argv[i], envp);
}

static void	bad_argument(void)
{
	int		i;
	char	*str;
	char	*s;

	i = 0;
	str = "\tError: Bad argument\n";
	while (str[i] != '\0')
	{
		write(2, &str[i], 1);
		i++;
	}
	i = 0;
	s = "\tEx: ./pipex <file1> <cmd1> <cmd2>...<file2>\n";
	while (s[i] != '\0')
	{
		write(1, &s[i], 1);
		i++;
	}
}

static void	fin_commande(char argc, char **argv, char **envp)
{
	int		fileout;

	
	if (argv[argc -1][0] == '/')
		commad_path(argv[argc - 1], envp);
	else if (argv[argc - 1][0] == '.' && argv[argc - 2][1] == '/')
		run_script(argv[argc - 1], envp);
	else
		execute(argv[argc - 1], envp);
}

static void	lop(char **argv, char **envp)
{
	int		i;
	int		fd[2];
	pid_t	*pids;
	int len;
	int f0;
	int f1;

	f1 = dup(STDOUT_FILENO);
	f0 = dup(STDIN_FILENO);
	if(!argv || !envp)
		return ;
	len = ft_strlen_2_erra(argv);
	pids = ft_calloc(len, sizeof(pid_t));
	i = 0;
	while (argv[i])
	{
		// filecommade(argv, envp, argc);
		if (pipe(fd) == -1)
			erro();
		pids[i] = fork();
		if (pids[i] == 0 && i != len - 1)
			child_process(argv, envp, fd, i);
		else if (pids[i] == 0 && i == len - 1)
			fin_commande(len, argv, envp);
		whilloop(fd);
		i++;
	}
	wit_process(len, &pids, fd,f1,f0);
}

int	main(int argc, char *argv[], char **envp)
{
	char	*cmd_line;
	char	**cmd;
	char	**env;
	int i;

	if (argc != 1)
	{
		ft_putstr_fd("Error\n", 2);
		exit(EXIT_FAILURE);
	}
	env = get_erray_env(get_env(envp));
	while (1)
	{
		cmd_line = readline("minishell-$");
		if(cmd_line == NULL)
			break;
		add_history(cmd_line);
		printf("%s\n", cmd_line);
		cmd = ft_split_pipe(cmd_line);
		lop (cmd, env);
		free(cmd_line);
		cmd_line = NULL;
	}
	i = 0;
	while(env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}