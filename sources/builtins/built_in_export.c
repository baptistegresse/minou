#include "../../includes/minishell.h"

void bubble_sort(t_env **head)
{
    int swapped;
    t_env *ptr1 = *head;
    t_env *lptr = NULL;
 
    // Cas de base : si la liste est vide ou contient un seul élément
    if (*head == NULL)
        return;
 
    do {
        swapped = 0;
        ptr1 = *head;
 
        while (ptr1->next != lptr) {
            if (strcmp(ptr1->key, ptr1->next->key) > 0) {
                // Échanger les noeuds
                t_env *temp = ptr1->next;
                ptr1->next = temp->next;
                temp->next = ptr1;
                if (ptr1 == *head)
                    *head = temp;
                ptr1 = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void ft_print_sorted_linked_list(t_env *head)
{
    // Copier la liste chaînée
    t_env *copy = NULL, *src = head;
    while (src) {
        t_env *new_node = malloc(sizeof(t_env));
        if (!new_node) {
            // Gérer l'échec d'allocation de mémoire
            fprintf(stderr, "Erreur : échec d'allocation de mémoire.\n");
            exit(EXIT_FAILURE);
        }
        new_node->key = strdup(src->key);
        new_node->value = strdup(src->value);
        new_node->next = copy;
        copy = new_node;
        src = src->next;
    }
 
    // Trier la copie de la liste chaînée
    bubble_sort(&copy);
 
    // Afficher la liste chaînée triée
    printf("Liste chaînée triée en ordre alphabétique selon la clé :\n");
    while (copy) {
        printf("%s=%s\n", copy->key, copy->value);
        copy = copy->next;
    }
 
    // Libérer la mémoire allouée pour la copie de la liste chaînée
    while (copy) {
        t_env *temp = copy;
        copy = copy->next;
        free(temp->key);
        free(temp->value);
        free(temp);
    }
}

void    ft_built_in_export(t_env **head, char *string)
{
    char    **var_list;
    size_t  i;

    i = 1;
    var_list = ft_lexer(string, ' ');
    if (!var_list[1])
        ft_print_sorted_linked_list(*head);
    while (var_list[i])
    {
    	char *equal = ft_strchr(var_list[i], '=');
    	if (equal)
    	{
      		*equal = '\0';
      		*head = add_node(*head, var_list[i], equal + 1);
    	}
        else
            *head = add_node(*head, var_list[i], "''");
        i++;
    }
}