#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

void	*ft_calloc(int count, int size);
char	**list_directory(char *path, int *count);
int		match_pattern(char *filename, char *pattern);

#endif
