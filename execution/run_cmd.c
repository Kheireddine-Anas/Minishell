#include "../minishell.h"
static int strlen_2darray(char **str)
{
	int i;

	if (!str ||!*str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
char **prepend_string_to_array(char **array, char *string)
{
	int i = 0;
	int array_length;
	char **new_array;
	int j = 0;

	array_length = strlen_2darray(array);
    new_array = malloc((array_length + 2) * sizeof(char *));
    if (new_array == NULL)
        exit(EXIT_FAILURE);
    new_array[0] = strdup(string);
    while (i < array_length)
    {
        new_array[i+ 1] = array[j];
		i++;
		j++;
    }
    new_array[i +1] = NULL;
    return (new_array);
}

char	*get_path(char **envp, char *cmd, int i)
{
	char	*path_new;
	char	*path;
	char	**path_split;

	path_new = NULL;
	path = NULL;
	while (envp[i++])
	{
		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
		{
			path = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) + 5; 
			break ;
		}
	}
	i = 0;
	path_split = ft_split(path, ':');
	{
		if (!path_split)
			exit(1);
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

void	commad_path(t_cmd *cmd, char **envp)
{
	char	**str_cmd;
	int		i;
	char	*path;

	i = 0;
	str_cmd = prepend_string_to_array(cmd->option,cmd->cmd);
	if(!str_cmd)
		exit(1);
	path = str_cmd[0];
	if (!path)
	{
		i = 0;
		while (str_cmd[i])
			free(str_cmd[i++]);
		free(str_cmd);
	}
	if (execve(path, str_cmd, envp) == -1)
	{
		printf("\033[1;31mminishell : %s : %s\033[0m\n",cmd->cmd, strerror(errno));
		exit(0);
	}
}

void	execute(t_cmd	*cmd, char **envp)
{
	int		i;
	char	*path;
	char 	**str_cmd;

	i = 0;
	str_cmd = prepend_string_to_array(cmd->option, cmd->cmd);
	path = get_path(envp, cmd->cmd, 0);
	// if (!path)
	// {
	// 	i = 0;
	// 	while (str_cmd[i])
	// 		free(str_cmd[i++]);
	// 	free(str_cmd);
	// }
	if (execve(path, str_cmd, envp) == -1)
	{
		printf("\033[1;31mminishell xas: %s : %s\033[0m\n",cmd->cmd, strerror(errno));
		exit(0);
	}
}

void	run_script(t_cmd	*cmd, char **envp)
{
	char	**str_cmd;

	str_cmd = malloc(2 * sizeof(char *));
	if (!str_cmd)
		exit(1);
	str_cmd[0] = cmd->cmd;
	str_cmd[1] = NULL;
	if (execve(str_cmd[0], str_cmd, envp) == -1)
	{
		printf("\033[1;31mminishell : %s : %s033[0m\n",str_cmd[0], strerror(errno));
		exit(0);
	}
}
