#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_env
{
  char *key;
  char *value;
  struct s_env *next;
} t_env;

t_env *new_node(char *key, char *value)
{
  t_env *node = (t_env*)malloc(sizeof(t_env));
  node->key = strdup(key);
  node->value = strdup(value);
  node->next = NULL;
  return node;
}

t_env *add_node(t_env *head, char *key, char *value)
{
  t_env *node = new_node(key, value);
  node->next = head;
  return node;
}

void  ft_print_env

int main(int argc, char *argv[], char *envp[])
{
  t_env *head = NULL;

  for (int i = 0; envp[i]; i++)
  {
    char *equal = strchr(envp[i], '=');
    if (equal)
    {
      printf("%s", equal);
      *equal = '\0';
      head = add_node(head, envp[i], equal + 1);
    }
  }

 
  for (t_env *node = head; node; )
  {
    t_env *temp = node->next;
    free(node->key);
    free(node->value);
    free(node);
    node = temp;
  }

  return 0;
}