#include "mini.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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
	t_env	*head;
	t_env	*tmp;
	int		i;

	i = 0;
	head = set_env(envs[i++]);
	printf("%s\n", envs[0]);
	tmp = head;
	while (envs[i])
	{
		tmp->next = set_env(envs[i]);
		tmp = tmp->next;
		i++;
	}
	while (head)
	{
		printf("%s%s\n", head->variable, head->value);
		head = head->next;
	}
	return 0;
}
