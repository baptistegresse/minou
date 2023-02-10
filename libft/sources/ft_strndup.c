#include "../includes/libft.h"

char *ft_strndup(char *s, size_t n)
{
    char    *new;
    
    new = malloc(n + 1);
    if (new)
    {
        ft_strncpy(new, s, n);
        new[n] = '\0';
    }
    return (new);
}
