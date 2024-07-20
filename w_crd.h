#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

void	*ft_calloc(int count, int size);
char	**list_directory(const char *path, int *count);
int		match_pattern(const char *filename, const char *pattern);
void	execute_command_with_wildcard(char *argv[]);
void	handle_command(int argc, char *argv[]);

#endif
