#include "minishell.h"

static char	*remove_spaces_and_single_quotes(const char *str)
{
    char	*dst;
    int		i;

    i = 0;
    dst = ft_calloc(ft_strlen(str) + 1,1);
    if (!dst)
        exit(EXIT_FAILURE);
    while (*str)
    {
        if(*str != '\"' && *str != '\'')
            dst[i++] = *str;
        str++;
    }
    dst[i] = '\0';
    return (dst);
}

static void	add_arg_to_cmd(char **cmd, int *size, char *start_ptr)
{
	char	*arg;

	arg = remove_spaces_and_single_quotes(start_ptr);
	cmd[*size] = arg;
	(*size)++;
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
		else if (**end_ptr == ' ' && (in_single_quotes % 2) == 0  && (in_double_quotes % 2) != 0)
		{
			**end_ptr = '\0';
			if (size >= *capacity - 1) 
				*cmd = realloc_cmd(cmd, capacity);
			add_arg_to_cmd(*cmd, &size, *start_ptr);
			*start_ptr = *end_ptr + 1;
		}
		else if( **end_ptr == ' ' && (in_double_quotes % 2) == 0 &&  (in_single_quotes % 2) != 0 )
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

char	**split_singl_qot(const char *command)
{
	int		capacity;
	char	*start_ptr;
	char	*end_ptr;
	char	**cmd;

	if (!command)
		return (NULL);
	capacity = 10;
	cmd = ft_calloc(capacity , sizeof(char *));
	if (!cmd)
		exit(EXIT_FAILURE);
	start_ptr = ft_strdup(command);
	end_ptr = start_ptr;
	process_char(&cmd, &capacity, &start_ptr, &end_ptr);
	return (cmd);
}
// int main ()
// {
// 	char **cmd;
// 	char *str = "echo 'hello' \"";
// 	int i = 0;

// 	cmd = split_singl_qot(str);
// 	while (cmd[i])
// 	{
// 		printf("%s\n", cmd[i]);
// 		i++;
// 	}
// 	return (0);
// }
