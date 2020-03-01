/**
 * soluciones.c
 *
 *  Created on: X/X/2020
 *  Author: "Aquí va tu nombre"
 */

#include "includes/problemas.h"
#include "includes/booleans.h"
#include "includes/list_node.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

struct list_node *getByIndex(struct list_node *list, int index)
{
    struct list_node *current = list;

    int count = 0;
    while (current != NULL)
    {
        if (count == index)
            return current;
        count++;
        current = current->next;
    }

    return current;
}

/**
 * 
 */
struct list_node *list_create_copy(struct list_node *list)
{
    struct list_node *temp = NULL;
    struct list_node *actual = list;

    struct list_node *original, *copia;

    if (list == NULL)
        return list;

    while (actual)
    {
        temp = actual->next;
        actual->next = (struct list_node *)malloc(sizeof(struct list_node));
        actual->next->value = actual->value;
        actual->next->next = temp;
        actual = temp;
    }
    actual = list;

    while (actual)
    {
        if (actual->next && actual->rand)
        {
            actual->next->rand = actual->rand->next;
        }
        actual = actual->next ? actual->next->next : actual->next;
    }

    original = list;
    copia = list->next;
    temp = copia;
    while (original && copia)
    {
        if (original->next)
            original->next = original->next->next;
        if (copia->next)
            copia->next = copia->next->next;
        original = original->next;
        copia = copia->next;
    }

    return temp;
}
/**
 * Implementación del algoritmo de ordenación heapsort
 */
void heap_sort(int *array, size_t size)
{
}

/**
 * Esta función inserta una nodo en una lista simplemente 
 * ligada y ordenada ascendentemente.
 * Después de la insersión la lista conserva su orden.
 * @param list - apuntador a la lista donde ser realizará la incersión
 * @param new_node - nodo que será insertado
 */
void list_insert_node(struct list_node **list, struct list_node *new_node)
{
}

/**
 * Estructura de lista ligada.
 */
struct list_pointer
{
    void *old;
    struct list_pointer *next;
};

/**
 *Busca un elemento en una lista de tipo list_pointer y a partir del valor almacenado en old
 *return 0 si no lo encuentra el valor de new contenido en el nodo en el que lo encontró
 */
unsigned long search_pointer(void *p, struct list_pointer *list)
{
    while (list != NULL)
    {
        if (list->old == p)
        {
            return 1;
        }
        list = list->next;
    }

    return 0;
}

/**
 * Agrega un elemento al principio de una lista de apuntadores
 * con los valores old y new que se pasan como parametros
 */
void push_pointer(void *old, struct list_pointer **list)
{
    struct list_pointer *new_node = (struct list_pointer *)malloc(sizeof(struct list_pointer));
    new_node->old = old;
    new_node->next = *list;
    *list = new_node;
}

/**
 * Esta función decide si la lista 'list' tiene un ciclo.
 * @param list
 * @return TRUE si tiene ciclo, FALSE en caso contrario
 */
int list_has_cycle(struct list_node *list)
{
    return false;
}

/**
 * Esta función decide si dos cadenas son anagramas.
 * @param string1 - cadena 1
 * @param string2 - cadena 2
 * @return TRUE si string1 y strin2 son anagramas, FALSE en caso contrario
 */
int anagrams(char *string1, char *string2)
{
    return false;
}

/**
 * Esta genera la tabla de del método de multiplicación egipcia.
 * Regresa un arreglo unidimencional de enteros.
 */
long long *egypcian_multiplication(int n, int _m)
{
    return NULL;
}

/**
 * Para un arreglo de enteros calcula el máximo valor 
 */
long long calc_max_sum(int *array, size_t size)
{
    return 0;
}
