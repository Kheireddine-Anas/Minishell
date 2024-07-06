#include "minishell.h"

static char	*remove_spaces_and_single_quotes(char *str)
{
    char	*dst;
    int		i;

    i = 0;
    dst = ft_calloc(ft_strlen(str) + 1,1);
    if (!dst)
        exit(EXIT_FAILURE);
    if(chek_tow_qoute(str ,'\'') == 1)
    {
        while (*str)
	    {
			if(*str == '\'')
				str++;
		    else if (*str == '\'' && (*(str + 1) == '{' || *(str - 1) == '}'))
			    str++;
			else 
		    {
				dst[i++] = *str;
				str++;
			}
	    }
    }
    else if(str[0] == '\'')
    {
		ft_putstr_fd("error in qoute\n",2);
		exit(1);
        while (*str)
        {
            dst[i++] = *str;
            str++;
        }
    }
     dst[i] = '\0';
    return (dst);
}

static void	add_arg_to_cmd(char **cmd, int *size, char *start_ptr)
{
	char	*arg;
    char	**str;
    int i = 0;
    
	arg = remove_spaces_and_single_quotes(start_ptr);
    if (ft_strchr(arg,'$') )
	{
		str = splite_variable(arg);
		while(str[i])
		{
			cmd[*size] = str[i];
			(*size)++;
			i++;
		}
	}
	if(ft_strlen(arg) > 0)
	{
		cmd[*size] = arg;
		(*size)++;
	}
}

static void	process_char(char ***cmd, int *capacity, 
		char **start_ptr, char **end_ptr)
{
	int	in_single_quotes;
	int in_double_quotes;
	int	size ;

	size = 0;
	in_single_quotes = 0;
	in_double_quotes = 0;
	while (**end_ptr)
	{
		if (**end_ptr == '\'' && (in_double_quotes % 2) == 0)
			in_single_quotes++;
        else if (**end_ptr == '\"' && (in_single_quotes % 2) == 0)
            in_double_quotes++;
		
		if (**end_ptr == ' ' && (in_single_quotes % 2) == 0 && (in_double_quotes % 2) == 0)
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

char	**split_qot(const char *command, char **envp)
{
	int		capacity;
	char	*start_ptr;
	char	*end_ptr;
	char	**cmd;
    int		j = 0;
	int     k = 0;
	char    *tmp;
	char    *variable;

	if (!command)
		return (NULL);
	capacity = 10;
	cmd = ft_calloc(capacity , sizeof(char *));
	if (!cmd)
		exit(EXIT_FAILURE);
	start_ptr = ft_strdup(command);
	end_ptr = start_ptr;
	process_char(&cmd, &capacity, &start_ptr, &end_ptr);
	// if (!cmd)
	// 	return (NULL);
	// while (cmd[j] )
	// {
	// 	variable = ft_strchr(cmd[j], '$');
    // 	if (cmd[j] &&  variable!= NULL && !ft_strchr(cmd[j], '\'') )
    // 	{
    //     	tmp = cmd[j];
    //     	cmd[j] = ft_strdup (chercher_variable(variable, envp));
    //     	if (ft_strlen(cmd[j]) == 0)
    //         k = 1;
    //     	free(tmp);
    // 	}
    // 	j++;
	// }
	// if (k == 1)
	// {
	// 	cmd = create_cmmmand(cmd);
	// }
	return (cmd);
}
int main (int argc,char **argv, char **envp)
{
	char **str;
	int i = 0;
	(void)argc;
	(void)argv;
	str = split_qot("echo 'hello $USER $PATH'csdcdscds'", envp);
	while(str[i])
	{
		printf("%s\n",str[i]);
		i++;
	}
	return (0);
}
