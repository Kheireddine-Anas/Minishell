#include "minishell.h"

void	cmd_export(t_env *env, char *add)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
		tmp = tmp->next;
	if (*add == '=')
	{
		
	}
	tmp->next = set_env(add);
	// printf("%s\n", tmp->variable);
	// printf("%s\n", env->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->next->value);
}
