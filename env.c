#include "mini.h"

char	*set_name(char *str)
{
	int	i;
	char	*name;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = ft_calloc(i + 1, 1);
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
		return (NULL);
	value = ft_calloc((ft_strlen(str) - i) , 1);
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
	head->value = set_value(str);
	head->next = NULL;
	return (head);
}

int main(int ac, char **av, char **envs)
{
	t_env	*env;
	t_env	*tmp;
	int		i;

	i = 0;
	env = set_env(envs[i++]);
	tmp = env;
	while (envs[i])
	{
		tmp->next = set_env(envs[i]);
		tmp = tmp->next;
		i++;
	}
	cmd_cd((av + 1), env);
	// while (env)
	// {
	// 	printf("%s=%s\n", env->variable, env->value);
	// 	env = env->next;
	// }
	return 0;
}
