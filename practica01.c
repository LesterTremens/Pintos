#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**
 * función busqBinaria: Toma O(logN) -> esto es menor que lineal.
 * calculamos el indice de enmedio y preguntamos y el medio-ésimo elemento es igual al índice, si lo es, existe al menos 1 y terminamos
 * sino, suponemos el el m-esimo es mayoy, de ser así, nos llamamos recursivamente en la parte superior (derecha), sino, en la parte inferior(izquierda)
 * si no se cumple la clausula de escape (a[i]=i]), devolvemos -1.
*/
int busquedaBinaria(int arr[], int l, int r)
{
    if (l <= r)
    {
        int medio = (l + r) / 2;
        if (arr[medio] == medio)
        {
            printf("Se encontró un elemento de la forma A[i]=i -> %d \n", medio);
            return medio;
        }
        else if (arr[medio] < medio)
        {
            return busquedaBinaria(arr, (medio + 1), r);
        }
        else
        {
            return busquedaBinaria(arr, l, (medio - 1));
        }
    }

    return -1;
}

void assertBBinaria()
{
    /*Todos los elementos son distintos*/
    int arr1[5] = {0, 25, 45, 38, 56};
    int arr2[5] = {1, 1, 23, 34, 58};
    int arr3[5] = {1, 2, 2, 46, 56};
    int arr4[5] = {1, 2, 3, 3, 56};
    int arr5[5] = {1, 2, 3, 4, 4};
    int *arr[5] = {arr1, arr2, arr3, arr4, arr5};
    int i = 0;
    for (; i < 5; i++)
    {
        printf("Test, se espera un %i\n", i);
        int e = busquedaBinaria(arr[i], i, 5);
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
    printf("cadena inicial: %s\n", copyStr);
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
    printf("cadena revertida: %s\n", copyStr);
    return copyStr;
}
/*Toma una frase en reversa, la tokeniza por espacios en blanco, calcula reversa del token y las concatena al final*/
char *reverseWord(char *palabraReversa)
{
    printf("revertir-palabra %s\n", palabraReversa);
    int len = strlen(palabraReversa);
    char *result = (char *)malloc(len + 1);
    //int i = 0;
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

/**void printChar(char *cadena)
{
    int c = 0;
    while (cadena[c] != '\0')
    {
        printf("print char is: %c\n", cadena[c]);
        c++;
    }
}**/

void assertReverseWord(char *oracion, char *esperado)
{
    char *reversaFrase = reverse(oracion);
    char *reversaOracion = reverseWord(reversaFrase);

    int codeResult = strcmp(reversaOracion, esperado);
    if (strcmp(reversaOracion, esperado) == 0)
    {
        printf("La prueba es correcta: %d\n", codeResult);
        printf("ESPERADO:%s\n", esperado);
        printf("RESULTADO:%s\n", reversaOracion);
    }
    else
    {
        printf("ERROR, la prueba es incorrecta:%d\n", codeResult);
    }
}

int main()
{
    assertBBinaria();
    //int arr[5] = {1, 1, 2, 222, 4444};
    //int n = sizeof(arr) / sizeof(arr[0]); //tamaño del arreglo / tamaño del tipo de dato = long del array.
    //busquedaBinaria(arr, 2, n - 1);
    char oracion[] = "Hola mundo!";
    char expected[] = "mundo! Hola";
    //char *r = reverse(string);
    //reverseWord(r);
    assertReverseWord(oracion, expected);

    return 0;
}
