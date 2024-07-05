#include "minishell.h"

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

void	export_add(t_env *env, char **value)
{
	int		i;
	char	*var;

	i = 1;
	while (value[i])
	{
		var = set_name(value[i]);

	}
	
}

void	cmd_export(t_env *env, char **add)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	if (!add[1])
		show_exp(env);
	else
	{
		export_add(tmp, add);
	}
	// tmp->next = set_env(add);
	// printf("%s\n", tmp->variable);
	// printf("%s\n", env->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->value);
}
