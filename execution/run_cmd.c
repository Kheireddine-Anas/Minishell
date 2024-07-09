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
	int		i;
	char	*path;

	i = 0;
	path = cmd->option[0];
	if (!path)
	{
		i = 0;
		while (cmd->option[i])
			free(cmd->option[i++]);
		free(cmd->option);
	}
	if (execve(path, cmd->option, envp) == -1)
		error_ch(cmd->option[0]);
}

void	execute(t_cmd	*cmd, char **envp)
{
	int		i;
	char	*path;

	i = 0;
	path = get_path(envp, cmd->option[0], 0);
	if (!path)
	{
		i = 0;
		while (cmd->option[i])
			free(cmd->option[i++]);
		free(cmd->option);
	}
	if (execve(path, cmd->option, envp) == -1)
		error_ch(cmd->option[0]);
}

