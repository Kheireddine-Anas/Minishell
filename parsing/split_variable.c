#include "../minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **split_variable(const char *str)
{
    int i = 0, j = 0, k = 0;
    char **result = malloc((strlen(str) + 1) * sizeof(char *));
    char *temp = malloc(strlen(str) + 1);
    
    while (str[i] != '\0')
    {
        if (str[i] == ' ' || str[i] == '\'')
        {
            if (k > 0)
            {
                temp[k] = '\0';
                result[j++] = strdup(temp);
                k = 0;
            }
            temp[k++] = str[i++];
            temp[k] = '\0';
            result[j++] = strdup(temp);
            k = 0;
        }
        else if (str[i] == '$')
        {
            if (k > 0)
            {
                temp[k] = '\0';
                result[j++] = strdup(temp);
                k = 0;
            }
            temp[k++] = str[i++];
        }
        else
        {
            temp[k++] = str[i++];
        }
    }
    
    if (k > 0)
    {
        temp[k] = '\0';
        result[j++] = strdup(temp);
    }
    
    result[j] = NULL;
    free(temp);
    return result;
}

// int main()
// {
//     char **str;
//     int i = 0;
//     str = split_string("echo $HOME $USER $PATH'");
//     while (str[i])
//     {
//         printf("%s\n", str[i]);
//         free(str[i]); // Don't forget to free the memory
//         i++;
//     }
//     free(str); // Don't forget to free the memory
//     return 0;
// }