#include "minishell.h"

int	ft_isalpha(int c)
{
	return ((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
}

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

void	show_exp(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!(tmp->value))
			printf("declare -x %s\n", tmp->variable);
		else
		{
			printf("declare -x %s =\"%s\"\n", tmp->variable, tmp->value);
		}
		tmp = tmp->next;
	}
}
int	check_exp(char *name)
{
	int	i;

	i = 0;
	if (ft_isdigit(name[0]))
		return (1);
	while (name[i] && name[i] != '=')
	{
		if (!ft_isalpha(name[i]) && !ft_isdigit(name[i]))
			return (1);
		i++;
	}
	return (0);
}

void	add_exp(t_env *env, char *value, char *var)
{
	while (env)
	{
		if (!ft_strcmp(env->variable, var))
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
			env->next = set_env(value);
			break ;
		}
		env = env->next;
	}
}

void	export_add(t_env *env, char **value)
{
	int		i;
	char	*var;
	t_env	*tmp;

	tmp = env;
	i = 1;
	while (value[i])
	{
		var = set_name(value[i]);
		if (!check_exp(var))
			add_exp(tmp, value[i], var);
		else
		{
			printf("Valid Identifier\n"); //We Should set the EXIT status to 1
		}
		i++;
	}
}

void	cmd_export(t_env *env, char **add)
{
	t_env	*tmp;
	t_env	*tmp1;

	tmp = env;
	tmp1 = env;
	while (tmp->next)
		tmp = tmp->next;
	if (!add[1])
		show_exp(env);
	else
		export_add(tmp, add);
}
