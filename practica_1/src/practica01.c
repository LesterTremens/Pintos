#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h> //USAMOS INT_MIN e INT MAX para simular los INFINITOS

struct node
{
    int node_value;
    struct node *left;
    struct node *right;
};

typedef struct node b_tree;

// int exist_Ai_eq2_i (int* array, int array_size, int value); //Es el equivalente a busqueda binaria
char *invert_statement(char *statement);
int is_search_tree(b_tree *tree);

/**
 * función busqBinaria: Toma O(logN) -> esto es menor que lineal.
 * calculamos el indice de enmedio y preguntamos y el medio-ésimo elemento es igual al índice y a su vez al buscado, si lo es, existe 1 y terminamos
 * sino, suponemos el el m-esimo es mayoy, de ser así, nos llamamos recursivamente en la parte superior (derecha), sino, en la parte inferior(izquierda)
 * si no se cumple la clausula de escape (a[i]=i]), devolvemos -1.
*/
int busquedaBinaria(int arr[], int l, int r, int buscado)
{
    if (l <= r)
    {
        int medio = (l + r) / 2;
        if ((arr[medio] == medio) && (medio == buscado))
        {
            printf("Se encontró un elemento de la forma A[i]=i -> %d \n", medio);
            return medio;
        }
        else if (arr[medio] < medio)
        {
            return busquedaBinaria(arr, (medio + 1), r, buscado);
        }
        else
        {
            return busquedaBinaria(arr, l, (medio - 1), buscado);
        }
    }

    return -1;
}
void printArray(int arr[], int len)
{
    int i = 0;
    for (; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
}
void assertBBinaria()
{
    /*Todos los elementos son distintos*/
    int arr1[5] = {0, 25, 45, 55, 65};
    int arr2[5] = {-1, 1, 3, 7, 11};
    int arr3[5] = {-2, -1, 2, 6, 8};
    int arr4[5] = {-3, -2, -1, 3, 33};
    int arr5[5] = {-4, -3, -2, -1, 4};
    int *arr[5] = {arr1, arr2, arr3, arr4, arr5};
    int i;
    int random;
    int t = time(NULL);
    srand(t);
    for (i = 0; i < 5; i++)
    {
        random = rand() % 4 + 1;
        printf("Arreglo: {");
        printArray(arr[i], 5);
        printf("}");
        printf("\nTest, se busca un %d\n", random);
        int e = busquedaBinaria(arr[i], i, 5, random); //agregar un numero random entre 1 y 5
        if (i == e)
            printf("Prueba pasada\n");
        else
            printf("No paso :(\n");
    }
}

char *copia(char *original)
{
    int len = strlen(original);
    char *copy = (char *)malloc(len + 1);
    int i = 0;
    for (; i < len; i++)
    {
        copy[i] = original[i];
    }
    copy[i] = '\0';
    return copy;
}
/*funcion reverse. Dada una palabra, copia su valor con malloc y realiza la reversa en O(n)*/
char *reverse(char string[])
{
    char *copyStr = copia(string);
    //printf("cadena inicial: %s\n", copyStr);
    int i = 0;
    int j = strlen(copyStr) - 1;
    char tmp;
    while (i < j)
    {
        tmp = copyStr[i];
        copyStr[i] = copyStr[j];
        copyStr[j] = tmp;
        i++;
        j--;
    }
    //printf("cadena revertida: %s\n", copyStr);
    return copyStr;
}
/*Toma una frase en reversa, la tokeniza por espacios en blanco, calcula reversa del token y las concatena al final*/
char *reverseWord(char *palabraReversa)
{
    int len = strlen(palabraReversa);
    char *result = (char *)malloc(len + 1);
    char *token = strtok(palabraReversa, " ");
    while (token)
    {
        char *r = reverse(token);  //reversa de la primera palabra
        strcat(r, " ");            //concatenamos el espacio
        strcat(result, r);         //lo añadimos al resultado
        token = strtok(NULL, " "); //calculamos el siguiente token
    }
    result[len] = '\0'; //Quitamos el ultimo espacio metido por el token
    return result;
}

char *invert_statement(char *statement)
{
    char *reversaFrase = reverse(statement);
    return reverseWord(reversaFrase);
}

void assertInvertStatement()
{
    char oracion1[] = "Hola mundo!";
    char expected1[] = "mundo! Hola";
    char oracion2[] = "_Orlando & Angye_";
    char expected2[] = "Angye_ & _Orlando";
    char oracion3[] = "Programar es lo maximo!";
    char expected3[] = "Mentira";
    char oracion4[] = " ¡¡ P = NP !!";
    char expected4[] = "Esto sera falso";
    char *oraciones[] = {oracion1, oracion2, oracion3, oracion4};
    char *expected[] = {expected1, expected2, expected3, expected4};
    int i = 0;
    for (; i < 4; i++)
    {
        if (strcmp(invert_statement(oraciones[i]), expected[i]) == 0)
        {
            printf("La prueba es correcta\n");
            printf("ENTRADA:%s\n", oraciones[i]);
            printf("ESPERADO:%s\n", expected[i]);
            printf("RESULTADO:%s\n", invert_statement(oraciones[i]));
        }
        else
        {
            printf("ERROR,la prueba es incorrecta\n");
            printf("ENTRADA:%s\n", oraciones[i]);
            printf("ESPERADO:%s\n", expected[i]);
            printf("RESULTADO:%s\n", invert_statement(oraciones[i]));
        }
    }
}

/*Metodo para insertar nodos*/
struct node *insertar(b_tree *nodo, int value)
{
    if (nodo == NULL)
    {
        b_tree *temp = (struct node *)malloc(sizeof(struct node));
        temp->node_value = value;
        return temp;
    }
    if (value < nodo->node_value)
    {
        nodo->left = insertar(nodo->left, value);
    }
    else if (value > nodo->node_value)
    {
        nodo->right = insertar(nodo->right, value);
    }

    return nodo;
}
//Inserta de forma que no quede un arbol binario de busqueda
struct node *insertarC(b_tree *nodo, int value)
{
    if (nodo == NULL)
    {
        b_tree *temp = (struct node *)malloc(sizeof(struct node));
        temp->node_value = value;
        return temp;
    }
    if (value > nodo->node_value)
    {
        nodo->left = insertar(nodo->left, value);
    }
    else if (value < nodo->node_value)
    {
        nodo->right = insertar(nodo->right, value);
    }

    return nodo;
}


/*Recorrido en orden para sacar los elementos.*/
void recorre_inOrder(b_tree *root)
{
    if (root != NULL)
    {
        recorre_inOrder(root->left);
        printf("%d \n", root->node_value);
        recorre_inOrder(root->right);
    }
}

int validarBinaryTree(b_tree *tree, int min, int max)
{
    if (tree == NULL)
    {
        return 0;
    }
    if (((tree->node_value) <= min) || ((tree->node_value) > max))
    {
        //printf("Alguno de los subArboles no es un Arbol binario de busqueda:- ERROR");
        return 1;
    }

    return validarBinaryTree(tree->left, min, tree->node_value) && validarBinaryTree(tree->right, tree->node_value, max); //Un arbol es un ABB sii sus subarboles lo son.
}

int is_search_tree(b_tree *tree)
{

    return validarBinaryTree(tree, INT_MIN, INT_MAX);
}

void assertIsBST()//b_tree *tree)
{

    struct node *raiz1 = NULL;
    raiz1 = insertar(raiz1, 10);
    insertar(raiz1, 20);
    insertar(raiz1, 5);
    insertar(raiz1, 0);
    insertar(raiz1, 70);
    insertar(raiz1, 53);

    struct node *raiz2 = NULL;
    raiz2 = insertar(raiz2, 50);
    insertar(raiz2, 40);
    insertar(raiz2, 30);
    insertar(raiz2, 20);
    insertar(raiz2, 10);
    insertar(raiz2, 0);

    struct node *raiz3 = NULL;
    raiz3 = insertarC(raiz3, 10);
    insertarC(raiz3, 12);
    insertarC(raiz3, 21);
    insertarC(raiz3, 54);
    insertarC(raiz3, 76);
    insertarC(raiz3, 100);

    struct node *raiz4 = NULL;
    raiz4 = insertarC(raiz4, 10);
    insertarC(raiz4, 30);
    insertarC(raiz4, 32);
    insertarC(raiz4, 47);
    insertarC(raiz4, 100);
    insertarC(raiz4, 121);
    struct node *trees[4] = {raiz1, raiz2, raiz3, raiz4};

    int i = 0;
    for (; i < 4; i++){
      if (is_search_tree(trees[i]) == 0)
      {
        printf("Prueba pasada, el arbol recibido es un Arbol Binario de Busqueda Valido\n");
      }
      else
      {
        printf("Prueba no pasada, el arbol no es un Arbol Binario de Busqueda Valido\n");
      }
    }
}

int main()
{
    assertBBinaria();
    assertInvertStatement();
    assertIsBST();
    return 0;
}
