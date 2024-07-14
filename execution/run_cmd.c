#include "../minishell.h"


char	*get_path(char **envp, char *cmd, int i)
{
	char	*path_new;
	char	*path;
	char	**path_split;

	path_new = NULL;
	path = NULL;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
		{
			path = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) + 5; 
			break ;
		}
		i++;
	}
	if (!path)
		return (NULL);
	i = 0;
	path_split = ft_split(path, ':');
	{
		if (!path_split)
			return (NULL);
	}
	while (path_split[i])
	{
		path_split[i] = strjoi(path_split[i], "/", cmd);
		if (access(path_split[i], X_OK) == 0)
		{
			path_new = path_split[i];
			break ;
		}
		i++;
	}
	return (path_new);
}

void	commad_path(t_cmd *cmd, char **envp ,t_status **status)
{
	int		i;
	char	*path;

	i = 0;
	path = cmd->option[0];
	(*status)->status = 0;
	if (execve(path, cmd->option, envp) == -1)
	{
		error_ch(status);
		exit(1);
	}
}

void	execute(t_cmd	*cmd, char **envp, t_status **status)
{
	int		i;
	char	*path;

	i = 0;
	path = get_path(envp, cmd->option[0], 0);
	(*status)->status = 0;
	if (execve(path, cmd->option, envp) == -1)
	{
		error_ch(status);
		exit(1);
	}
}

