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
    struct list_node *resultado = NULL;
    struct list_node *actual = list;

    struct list_node *original, *copiado;

    if (list == NULL)
        return list;

    while (actual)
    {
        resultado = actual->next;
        actual->next = (struct list_node *)malloc(sizeof(struct list_node));
        actual->next->value = actual->value;
        actual->next->next = resultado;
        actual = resultado;
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
    copiado = list->next;
    resultado = copiado;
    while (original && copiado)
    {
        if (original->next)
            original->next = original->next->next;
        if (copiado->next)
            copiado->next = copiado->next->next;
        original = original->next;
        copiado = copiado->next;
    }

    return resultado;
}
/*funcion para ajustar los elementos del heap a partir del nodo i*/
void heapify(int *array, size_t size, int i)
{
    int mayor;
    int temporal;
    int l = 2 * i + 1; //hijos izquierdos
    int r = 2 * i + 2; //hijos deremos
    if (l < size && array[l] > array[i])
        mayor = l;
    else
        mayor = i;

    if (r < size && array[r] > array[mayor])
        mayor = r;
    if (mayor != i)
    {
        temporal = array[i];
        array[i] = array[mayor];
        array[mayor] = temporal;
        heapify(array, size, mayor);
    }
}
/**
 * Implementación del algoritmo de ordenación heapsort
 */
void heap_sort(int *array, size_t size)
{
    int i;
    /*indexamos el array*/
    for (i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    i = 0;
    for (i = size - 1; i >= 0; i--)
    {
        int temp = array[0]; //hacemos swap con el final y la raiz
        array[0] = array[i];
        array[i] = temp;

        heapify(array, i, 0); //reajustamos
    }
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
    /*Si ambos son nulos, la prueba pasa por vacuidad*/
    /*si no hay nada en la lista, el nodo se incializa como la lista (insercion simple)*/
    if (*list == NULL && new_node != NULL)
    {
        new_node->next = *list;
        *list = new_node;
        return;
    }
    /*caso 3 la lista esta llena y el nodo no es null*/
    if (*list != NULL && new_node != NULL)
    {
        if ((*list)->value > new_node->value) //insercion en la cabeza, el valor es mas chico que head
        {
            new_node->next = *list;
            *list = new_node;
        }
        else
        {
            struct list_node *actual; //creamos un temporal para iterar que apunte a la cabeza
            actual = *list;
            while (actual->next != NULL &&
                   actual->next->value < new_node->value)
            {
                actual = actual->next; //pescamos la referencia inmediata menor donde irá new_node
            }
            new_node->next = actual->next; //asignamos los apuntadores el siguiente del nuevo es el siguiente del anterior
            actual->next = new_node;       //el siguiente del anterior es el siguiente del nuevo
            return;                        //acabamos
        }
    }
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
    /*usamos el algoritmo de floyd (la tortuga y el conejo)
    El conejo siempre irá por delante de la tortuga, si la tortuga avanza un paso, el conejo se mueve 2.
    eventualmente se alcanzarán y ahí es donde sabemos que habrá un ciclo
    */

    if (list != NULL)
    {
        struct list_node *tortuga = list;
        struct list_node *conejo = list;
        while (true)
        {
            tortuga = tortuga->next;
            if (conejo->next != NULL)
            {
                conejo = conejo->next->next;
            }
            else
            {
                return false;
            }
            if (tortuga == NULL || conejo == NULL)
            {
                return false;
            }
            if (tortuga == conejo)
            {
                return true;
            }
        }
    }
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
    if (string1 != NULL && string2 != NULL)
    {
        int sizeStr1 = strlen(string1);
        int sizeStr2 = strlen(string2);
        if (sizeStr1 != sizeStr2)
        {
            //printf("Las palabras son de tamaños diferentes");
            return false;
        }

        char *resultTokenizeStr1 = (char *)malloc(sizeStr1 + 1);
        char *tokenStr1 = strtok(string1, " ");
        while (tokenStr1)
        {
            strcat(resultTokenizeStr1, tokenStr1); //lo añadimos al resultado
            tokenStr1 = strtok(NULL, " ");         //calculamos el siguiente token
        }
        resultTokenizeStr1[sizeStr1] = '\0'; //Quitamos el ultimo espacio metido por el token

        char *resultTokenizeStr2 = (char *)malloc(sizeStr2 + 1);
        char *tokenStr2 = strtok(string2, " ");
        while (tokenStr2)
        {
            strcat(resultTokenizeStr2, tokenStr2); //lo añadimos al resultado
            tokenStr2 = strtok(NULL, " ");         //calculamos el siguiente token
        }
        resultTokenizeStr2[sizeStr2] = '\0'; //Quitamos el ultimo espacio metido por el token
    }
    return false;
}

unsigned long long multiply(unsigned long long a, unsigned long long b)
{
    unsigned long long result = 0;

    while (a > 0)
    {
        if (a & 1)
        {
            result += b;
        }
        // divide a entre 2 y trunca el resultado
        a = a >> 1;
        // multiplica b por 2
        b = b << 1;
    }
    return result;
}

struct list_node *listaVal( int n)
{
  struct list_node *list =(struct list_node *)malloc(sizeof(struct list_node));
  struct list_node *valor = (struct list_node *)malloc(sizeof(struct list_node));
  int i = 1;
  valor -> value = i;
  push_front(valor->value,&list);
  while(i <= n)
  {
    i = multiply(i,2);
    valor->value = i;
    if(i <= n)
    {
      //printf("%d\n", valor->value);
      push_front(valor->value,&list);
    }
  }
  free_list(list);
  free_list(valor);
  return list;
}

/**
 * Esta genera la tabla de del método de multiplicación egipcia.
 * Regresa un arreglo unidimencional de enteros.
 */
long long *egypcian_multiplication(int n, int m)
{
    struct list_node *listC =(struct list_node *)malloc(sizeof(struct list_node));
    struct list_node *listV = listaVal(n);
    long long sum = 0;
    long long vl = listV -> value;
    push_front(vl, &listC);
    long long sumF = 0;
    long long *resultado;
    long long len = 0;
    long long con = 1;

    while(sum != n)
    {
      //printf("%lld\n",vl );
      if(vl < n){
        listV = listV -> next;
        vl += listV -> value;
        push_front(listV -> value, &listC);
        //printf("%lld\n",vl );
      }
      if(vl > n){
        vl -= listV -> value;
        pop(&listC);
        listV = listV -> next;
        vl += listV -> value;
        push_front(listV -> value, &listC);
        //printf("%lld\n",vl);
      }
      if(vl == n){
        sum = vl;
        //printf("Listo %lld\n",vl);
      }
    }

    len = list_length(listC) + 1;
    //printf("Soy la lista y mi tmañano es %lld\n", len );
    resultado = (long long*)malloc(len * sizeof(long long*));
    resultado[0] = len +1;
    while(listC)
    {
      //printf("%lld\n",(long long)listC -> value );
      if(listC -> value != 0)
      {
        sumF += multiply(listC -> value , m);
        resultado[con] = multiply(listC -> value , m);
        con ++;
        //printf("%lld\n",sumF );
      }
      listC = listC -> next;
    }
    resultado[len] = sumF;
    free(resultado);
    free_list(listC);
    return resultado;
}




/**int findSuma(struct list *list, int n){

}*/

/**
 * Para un arreglo de enteros calcula el máximo valor
 */
long long calc_max_sum(int *array, size_t size)
{
    return 0;
}
