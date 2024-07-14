#include "../minishell.h"

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

env_t	*seenv_t(char *str)
{
	env_t	*head;

	head = ft_calloc(1, sizeof(env_t));
	head->key = set_name(str);
	// printf(">>>>>>>>>>>>>>>>>%s\n", head->key);
	head->value = set_value(str);
	// printf(">>>>>>>>>>>>>>>>>%s\n", head->value);
	head->next = NULL;
	return (head);
}

void	show_exp(env_t *env)
{
	env_t	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!(tmp->value))
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s =\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}


int	check_exp(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]) || name[0] == '=')
		return (1);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]))
			return (1);
		i++;
	}
	return (0);
}

void	add_exp(env_t *env, char *value, char *var)
{
	while (env)
	{
		if (!ft_strcmp(env->key, var))
		{
			free(var);
			var = set_value(value);
			if (var)
			{
				free(env->value);
				env->value = var;
			}
			break ;
		}
		if (!env->next)
		{
			env->next = seenv_t(value);
			break ;
		}
		env = env->next;
	}
}

void	export_add(env_t **env, char **value)
{
	int		i;
	char	*var;
	env_t	*tmp;

	tmp = *env;
	i = 1;
	while (value[i])
	{

		var = set_name(value[i]);
		// printf("///%s///*%s*///\n", value[i], var); //We Should set the EXIT status to 1
		if (!check_exp(value[i]))
			add_exp(tmp, value[i], var);
		else
			ft_putstr_fd("invalid Identifier\n", 2); //We Should set the EXIT status to 1
		i++;
	}
}

void	cmd_export(env_t **env, char **add)
{

	if (!add[1])
		show_exp(*env);
	else
		export_add(env, add);
}