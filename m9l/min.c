#include "mini.h"

void handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

int main()
{
	char	*input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		input = readline("Enter CMD: ");
		if (!input)
		{
			printf("\nCtrl+D pressed. Exiting...\n");
			break;
		}
			add_history(input);
			printf("CMD: %s\n", input);
			free(input);
	}
	return 0;
}