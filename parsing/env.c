#include "../minishell.h"
char	*strjoin_1(char *s1, char *s2, int val)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!str)
		return (0);
	while (i[s1])
	{
		str[i] = s1[i];
		i++;
	}
	if (val)
		str[i++] = '=';
	else
		str[i++] = '/';
	while (*s2)
		str[i++] = *s2++;
	str[i] = 0;
	if (!val)
		free(s1);
	return (str);
}
char	*set_name(char *str)
{
	int	i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_calloc(i + 1, sizeof(char));
	i = -1;
	while (str[++i] && str[i] != '=')
		name[i] = str[i];
	name[i] = '\0';
	return (name);
}

char	*set_value(char *str)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (ft_strdup(""));
	value = ft_calloc((ft_strlen(str) - i) , sizeof(char));
	i++;
	while (str[i])
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

t_env	*set_env(char *str)
{
	t_env	*head;

	head = ft_calloc(1, sizeof(t_env));
	head->variable = set_name(str);
	// printf(">>>>>>>>>>>>>>>>>%s\n", head->variable);
	head->value = set_value(str);
	// printf(">>>>>>>>>>>>>>>>>%s\n", head->value);
	head->next = NULL;
	return (head);
}

int	check_cmd(char *cmd)
{
	char	**paths;
	char	*check;
	int		i;

	i = 0;
	paths = ft_split(getenv("PATH"), ':');
	while (paths[i])
	{
		check = strjoin_1(paths[i], cmd, 0);
		if (!access(check, F_OK))
		{
			if (!access(check, X_OK))
				return (0);
			printf("Permission Denied: %s>>\n", cmd);
			return (1);
		}
		i++;
	}
	printf("CMD not found: %s<<\n", paths[1]);
	return (1);
}

char	**env_set(t_env *env)
{
	char	**envirs;
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		if (tmp->value && tmp->variable)
			i++;
		tmp = tmp->next;
	}
	envirs = ft_calloc((i + 1), sizeof(char *));
	i = 0;
	tmp = env;
	while (tmp)
	{
		envirs[i++] = strjoin_1(tmp->variable, tmp->value, 1);
		tmp = tmp->next;
	}
	// printf("%s\n", envirs[33]);
	return (envirs);
}
// int main(int ac, char **av, char **envs)
// {
// 	t_env	*env; //ENV struct
// 	t_env	*tmp;
// 	t_env	*tmp1;
// 	char	*input ;
// 	char	**envirs;
// 	int		i;
// 	char *str[] = {"cd","getNextLine"};
// 	i = 0;
// 	env = set_env(envs[i++]);
// 	tmp = env;
	
// 	while (envs[i])
// 	{
// 		tmp->next = set_env(envs[i]);
// 		tmp = tmp->next;
// 		i++;
// 	}
// 	envirs = env_set(env); //ENV as char **
// 	i = 0;
// 	cmd_cd(str, env);
// 	return 0;
// }