#include "minishell.h"
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char **split_and_include_symbols(const char *str)
{
    char **result = NULL;
    char *buffer = malloc(strlen(str) + 1);
    int i = 0, j = 0, k = 0;
    while (str[i] != '\0')
    {
        if ((str[i] == '>' || str[i] == '<'))
        {
            if (j != 0)
            {
                buffer[j] = '\0';
                result = realloc(result, sizeof(char *) * (k + 2));
                if (result == NULL)
                {
                    exit(EXIT_FAILURE);
                }
                result[k] = strdup(buffer);
                k++;
                j = 0;
            }
            buffer[j] = str[i];
            j++;
            if (str[i+1] == str[i])
            {
                buffer[j] = str[i+1];
                j++;
                i++;
            }
            buffer[j] = '\0';
            result = realloc(result, sizeof(char *) * (k + 2));
            if (result == NULL)
                exit(EXIT_FAILURE);
            result[k] = strdup(buffer);
            k++;
            j = 0;
        }
        else if (str[i] == ' ')
        {
            if (j != 0) // Avoid empty strings
            {
                buffer[j] = '\0';
                result = realloc(result, sizeof(char *) * (k + 2));
                if (result == NULL)
                {
                    exit(EXIT_FAILURE);
                }
                result[k] = strdup(buffer);
                k++;
                j = 0;
            }
        }
        else
        {
            buffer[j] = str[i];
            j++;
        }
        i++;
    }

    if (j != 0) // Add the last string if it's not empty
    {
        buffer[j] = '\0';
        result = realloc(result, sizeof(char *) * (k + 2));
        if (result == NULL)
        {
            exit(EXIT_FAILURE);
        }
        result[k] = strdup(buffer);
        k++;
    }

    result[k] = NULL; // Null terminate the array

    free(buffer);
    return result;
}

// int main ()
// {
//     char **result = split_and_include_symbols("echo  < \"<lim>>output.txt\"  dvdfdfdf");
//     int i = 0;
//     while (result[i] != NULL)
//     {
//         printf("%s\n", result[i]);
//         free(result[i]);
//         i++;
//     }
//     free(result);
//     return 0;
// }