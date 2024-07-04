#include "minishell.h"

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


int chek_herdoc(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while(str[i] && str[i + 1])
	{
		if ((str[i] == '<' && str[i +1] == '<') || (str[i] == '>' && str[i +1] == '>'))
		return (1);
		i++;
	}
	return (0);
}

// char	*get_path(char **envp, char *cmd, int i)
// {
// 	char	*path_new;
// 	char	*path;
// 	char	**path_split;

// 	path_new = NULL;
// 	path = NULL;
// 	while (envp[i++])
// 	{
// 		if (ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) != NULL)
// 		{
// 			path = ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])) + 5; 
// 			break ;
// 		}
// 	}
// 	i = 0;
// 	path_split = ft_split(path, ':');
// 	{
// 		if (!path_split)
// 			exit(1);
// 	}
// 	while (path_split[i])
// 	{
// 		path_split[i] = strjoi(path_split[i], "/", cmd);
// 		if (access(path_split[i], X_OK) == 0)
// 		{
// 			path_new = path_split[i];
// 			break ;
// 		}
// 		i++;
// 	}
// 	return (path_new);
// }
