#include "../minishell.h"

char *remove_single_qoute(char *str)
{
	char *dst;
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = strlen(str);
	dst = (char *)malloc(len + 1);
	if (!dst)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	if(str[0]== '\'' && str[len - 1]== '\'' && len != 1)
	{
		while (str[i++])
		{
			if (str[i] != '\'' && (str[i +1 ] != '{' || str[i -1 ] != '}'))
				dst[j++] = str[i];
		}
	}
	else
	{
		while (str[i])
		{
			dst[j++] = str[i];
			i++;
		}	
	}
	dst[j] = '\0';
	return (dst);
}
char *remove_doubl_qoute(char *str)
{
	char *dst;
	int i;
	int j;
	int len;

	i = 0;
	j = 0;
	len = strlen(str);
	dst = (char *)malloc(len + 1);
	if (!dst)
	{
		perror("Allocation error");
		exit(EXIT_FAILURE);
	}
	if(str[0]== '"' && str[len - 1]== '"' && len != 1)
	{
		while (str[i++])
		{
			if (str[i] != '"' && (str[i +1 ] != '{' || str[i -1 ] != '}'))
				dst[j++] = str[i];
		}
	}
	else
	{
		while (str[i])
		{
			dst[j++] = str[i];
			i++;
		}	
	}
	dst[j] = '\0';
	return (dst);
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

char *add_valu_variable(char *str, char **envp)
{
    if (!str)
        return NULL;

    char **str1 = NULL;
    int k = 0;
    int i = 0;
    int j = 0;
    char *variable;
    char *tmp;

    if (ft_strchr(str, '$'))
        str1 = split_variable(str);

    if (!str1)
        return NULL;

    while (str1[j])
    {
        variable = ft_strchr(str1[j], '$');
        if (str1[j] && variable != NULL && !ft_strchr(str1[j], '\''))
        {
            tmp = str1[j];
            str1[j] = ft_strdup(chercher_variable(variable, envp));
            if (!str1[j] || ft_strlen(str1[j]) == 0)
                k = 1;
            free(tmp);
        }
        j++;
    }

    if (k == 1)
        str1 = create_cmmmand(str1);

    str = NULL;
    while (str1 && str1[i])
    {
        if (str == NULL)
            str = ft_strdup(str1[i]);
        else
        {
            tmp = str;
            str = ft_strjoin(str, str1[i]);
            free(tmp);
        }
        i++;
    }

    return str;
}
char	*strjoi(char *s1, char *s2, char *s3)
{
    int		size_total;
    char	*res;
    int		i;
    int		j;

    j = 0;
    i = 0;
    if (!s1 || !s2 || !s3)
	{
		if(!s1)
			return (ft_strjoin(s2, s3));
		if(!s2)
			return (ft_strjoin(s1, s3));
		if(!s3)
			return (ft_strjoin(s1, s2));
	}
    size_total = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3) + 1;
    res = ft_calloc(size_total, 1);
    if (!res)
        return (NULL);
    while (s1[i] != '\0')
    {
        res[i] = s1[i];
        i++;
    }
    while (s2[j] != '\0')
        res[i++] = s2[j++];
    j = 0;
    while (s3[j] != '\0')
        res[i++] = s3[j++];
    res[i] = '\0';
    return (res);
}