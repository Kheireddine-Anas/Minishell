#ifndef MINISHELL_H
#define MINISHELL_H
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "libftt_/libft.h"
char	**split_singl_qot(const char *command);
char	**split_double_qot(const char *command);
#endif