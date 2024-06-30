#include "minishell.h"

int chek_string_spece(char *str)
{
	size_t i;

	i = 0;
	if(!str[i])
		return (0);
	while (str[i] && str[i] == ' ')
		i++;
	if(ft_strlen(str) == i)
		return (1);
	return (0);

}
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
char	*remove_spaces_and_single_quotes(const char *str)
{
	char	*dst;
	int		i;

	i = 0;
	dst = ft_calloc(ft_strlen(str) + 1,1);
	if (!dst)
		exit(EXIT_FAILURE);
	while (*str)
	{
		if (*str != '\"')
			dst[i++] = *str;
		// else if((*str == '\"' && *str++ == '\"' && *str+2 == ' ') || (*str-1 == ' ' && *str++ == '\"' && *str+2 == '\"'))
		// 	dst[i++] = ' ';
		str++;
	}
	dst[i] = '\0';
	return (dst);
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

void	add_arg_to_cmd(char **cmd, int *size, char *start_ptr)
{
	char	*arg;
	char	**str;
	int i = 0;

	arg = remove_spaces_and_single_quotes(start_ptr);
	if (ft_strchr(arg,'$'))
	{
		str = splite_variable(arg);
		while(str[i])
		{
			cmd[*size] = str[i];
			(*size)++;
			i++;
		}
	}
	else if(ft_strlen(arg) > 0)
	{
		cmd[*size] = arg;
		(*size)++;
	}
	// else if(chek_string_spece(arg) == 1)
	// {
	// 	cmd[*size] = arg;
	// 	(*size)++;
	// }
}

void	process_char(char ***cmd, int *capacity, 
		char **start_ptr, char **end_ptr)
{
	int	in_double_quotes;
	int	size ;

	size = 0;
	in_double_quotes = 0;
	while (**end_ptr)
	{
		if (**end_ptr == '\"')
			in_double_quotes++;
		else if (**end_ptr == ' '  && (in_double_quotes % 2) == 0)
		{
			**end_ptr = '\0';
			if (size >= *capacity - 1) 
				*cmd = realloc_cmd(cmd, capacity);
			add_arg_to_cmd(*cmd, &size, *start_ptr);
			*start_ptr = *end_ptr + 1;
		}
		(*end_ptr)++;
	}
	if (**start_ptr != **end_ptr)
	{
		if (size >= *capacity - 1) 
			*cmd = realloc_cmd(cmd, capacity);
		add_arg_to_cmd(*cmd, &size, *start_ptr);
	}
}

char	**split_double_qot(const char *command, char **envp)
{
	int		capacity;
	char	*start_ptr;
	char	*end_ptr;
	char	**cmd;
	int		j = 0;
	int k = 0;
	char *tmp;
	char *variable;

	if (!command)
		return (NULL);
	capacity = 10;
	cmd = ft_calloc(capacity , sizeof(char *));
	if (!cmd)
		exit(EXIT_FAILURE);
	start_ptr = ft_strdup(command);
	end_ptr = start_ptr;
	process_char(&cmd, &capacity, &start_ptr, &end_ptr);
	if (!cmd)
		return (NULL);
	while (cmd[j])
	{
		variable = ft_strchr(cmd[j], '$');
    	if (cmd[j] &&  variable!= NULL && !ft_strchr(cmd[j], '\'') )
    	{
        	tmp = cmd[j];
        	cmd[j] = ft_strdup (chercher_variable(variable, envp));
        	if (ft_strlen(cmd[j]) == 0)
            k = 1;
        	free(tmp);
    	}
    	j++;
	}
	if (k == 1)
	{
		cmd = create_cmd(cmd);
	}
	return (cmd);
}

char **create_cmd(char **str)
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
