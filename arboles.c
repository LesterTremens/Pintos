#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    int node_value;
    struct node *left;
    struct node *right;
};

typedef struct node b_tree;

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

    //printf("Valor Insertado:%d\n", value);

    return nodo;
}
/*Recorrido en orden para sacar los elementos.*/
void inorder(b_tree *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d \n", root->node_value);
        inorder(root->right);
    }
}
/*Metodo para decir si un ABB es (o no) un ABB válido*/
int main()
{
    struct node *raiz = NULL;
    raiz = insertar(raiz, 10);
    insertar(raiz, 20);
    insertar(raiz, 5);
    insertar(raiz, 0);
    insertar(raiz, 70);
    insertar(raiz, 53);

    inorder(raiz);
    return 0;
}