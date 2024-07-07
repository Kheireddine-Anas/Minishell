#include "../minishell.h"

void error_alocation(void)
{
	perror("Allocation error");
	exit(EXIT_FAILURE);
}