#include "minishell.h"



char *chercher_variable(char *str, char **envp)
{
	int i;
	char *variable;

	i = 0;
	variable = "\0";
	if (!str)
		return (variable);
	str++;
	if (*str != '\0')
	{
		str = ft_strjoin(str, "=");
		while (envp[i])
		{
			if (ft_strnstr(envp[i], str, ft_strlen(envp[i])) != NULL)
			{
				variable = ft_strnstr(envp[i], str, ft_strlen(envp[i])) + ft_strlen(str); 
				break ;
			}
			i++;
		}
		free(str);
	}
	return(variable);
}


char	**realloc_cmd(char ***cmd, int *capacity)
{
	int		i;
	char	**new_cmd;

	*capacity *= 2;
	new_cmd = ft_calloc(*capacity , sizeof(char *));
	if (!new_cmd)
	{
		free(*cmd);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < *capacity / 2)
	{
		new_cmd[i] = (*cmd)[i];
		i++;
	}
	free(*cmd);
	return (new_cmd);
}

char **create_cmmmand(char **str)
{
	int i;
	int j = 0;
	char **result;

	i = 0;
	if(!str || !*str)
		return (NULL);
	while(str[i])
	{
		i++;
	}
	result = ft_calloc(i , sizeof(char *));
	if (!result)
		exit(EXIT_FAILURE);
	i = 0;
	while (str[i])
	{
		if (ft_strlen(str[i]) > 0)
		{
			result[j] = str[i];
			j++;
		}
		i++;
	}
	result[j] = NULL;
	return (result);
}

int chek_tow_qoute(char *str, char c)
{
	int i;

	i = 0;
    if(str[0] == c && str[ft_strlen(str) - 1] == c)
        return (1);
	while(str[i])
	{
		if(str[i] == c && str[i + 1] == c)
			return (1);
		i++;
	}
    return (0);
}