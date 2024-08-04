#include "minishell.h"

char	*set_name(char *str)
{
	int		i;
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
	while (str[i] && str[i] != '=' && str[i] != ' ')
		i++;
	if (!str[i])
		return (ft_strdup(""));
	value = ft_calloc((ft_strlen(str) - i), sizeof(char));
	i++;
	while (str[i] && str[i] != '=' && str[i] != ' ')
		value[j++] = str[i++];
	value[j] = '\0';
	return (value);
}

t_env	*set_env(char *str)
{
	t_env	*head;

	head = ft_calloc(1, sizeof(t_env));
	head->variable = set_name(str);
	head->value = set_value(str);
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
		check = ft_join(paths[i], cmd, 0);
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
		envirs[i++] = ft_join(tmp->variable, tmp->value, 1);
		tmp = tmp->next;
	}
	return (envirs);
}

/*int main(int ac, char **av, char **envs)
{
	t_env	*env; //ENV struct
	t_env	*tmp;
	t_env	*tmp1;
	char	*input ;
	char	**envirs;
	int		i;

	i = 0;
	env = set_env(envs[i++]);
	tmp = env;
	tmp1 = env;
	
	while (envs[i])
	{
		tmp->next = set_env(envs[i]);
		tmp = tmp->next;
		i++;
	}
	cmd_export(env, av + 1); // HERE We export av[1] to env struct
	// while (tmp1) //Uncomment this loop to see ENV struct
	// {
	// 	printf("%s*****%s\n", tmp1->variable, tmp1->value);
	// 	tmp1 = tmp1->next;
	// }
	// while (1)
	// {
	// 	input = readline("Enter CMD: ");
	// 	if (!input)
	// 	{
	// 		printf("\nCtrl+D pressed. Exiting...\n");
	// 		break;
	// 	}
	// 	// cmd_unset(&env, "abcq");
	// 	add_history(input);
	// 	printf("CMD: %s\n", input);
	// 	free(input);
	// }
	envirs = env_set(env); //ENV as char **
	// check_cmd(av);
	// cmd_cd((av + 1), env);
	// cmd_cd((av + 2), env);
	i = 0;
	while (envirs[i]) //Uncomment this loop to see ENV struct
	{
		printf("%s\n", envirs[i++]);
	}
	// printf("******\n");
	return 0;
}
*/