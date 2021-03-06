#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../testing/inc/Employee.h"
#include "../inc/LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);
//static Node* newNode(void);

/** \brief Crea un nuevo Node en memoria de manera dinamica
 *
 *  \param void
 *  \return Node* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
/*
static Node* newNode(void)
{
   Node* this;
   this = (Node *)malloc(sizeof(Node));

   return this;
}
*/
/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        returnAux = this->size;
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;

    if(this != NULL)
    {
        if(nodeIndex >= 0 && nodeIndex < ll_len(this))
        {
            for(int i = 0; i < ll_len(this); i++)
            {
                if(pNode == NULL)
                {
                    pNode = this->pFirstNode;
                }
                else
                {
                    pNode = pNode->pNextNode;
                }

                if(i == nodeIndex)
                {
                    break;
                }
            }
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        Node* newNode = (Node *)malloc(sizeof(Node));
        Node* previousNode = (Node *)malloc(sizeof(Node));
        Node* nextNode = (Node *)malloc(sizeof(Node));

        if(nodeIndex == 0)
        {
            //PRIMER INDICE DE LA LISTA
            if(ll_len(this) == 0)
            {
                newNode->pElement = pElement;
                newNode->pNextNode = NULL;
            }
            else
            {
                nextNode = this->pFirstNode;
                newNode->pElement = pElement;
                newNode->pNextNode = nextNode;
            }
            this->pFirstNode = newNode;
        }
        else
        {
            previousNode = getNode(this, nodeIndex - 1);
            if(nodeIndex == ll_len(this))
            {
                //ES EL ULTIMO
                newNode->pElement = pElement;
                newNode->pNextNode = NULL;
                previousNode->pNextNode = newNode;
            }
            else
            {
                nextNode = getNode(this, nodeIndex + 1);
                newNode->pElement = pElement;
                newNode->pNextNode = nextNode;
                previousNode->pNextNode = newNode;
            }
        }

        this->size++;

        returnAux = 0;
    }
    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        addNode(this, ll_len(this), pElement);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;

    if(this != NULL)
    {
        if(index < ll_len(this))
        {
            Node* pNode = (Node*)malloc(sizeof(Node*));

            pNode = getNode(this, index);

            if(pNode != NULL)
            {
                returnAux = (void*)malloc(sizeof(void*));
                returnAux = pNode->pElement;
            }
        }
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(index >= 0 && index < ll_len(this))
        {
            Node* pNode = (Node*)malloc(sizeof(Node*));
            pNode = getNode(this, index);
            pNode->pElement = pElement;

            returnAux = 0;
        }
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int flagPrev = 0;
    int flagNext = 0;

    if(this != NULL)
    {
        if(index >= 0 && index < ll_len(this))
        {
            Node* pNode = (Node*)malloc(sizeof(Node*));
            Node* previousNode = (Node*)malloc(sizeof(Node*));
            Node* nextNode = (Node*)malloc(sizeof(Node*));

            pNode = getNode(this, index);

            if(pNode != this->pFirstNode)
            {
                //NO ES EL INDICE 0
                previousNode = getNode(this, index - 1);
                flagPrev = 1;
            }

            if(pNode->pNextNode != NULL)
            {
                //NO ES EL ULTIMO NODO
                nextNode = getNode(this, index + 1);
                flagNext = 1;
            }

            if(flagPrev == 1 && flagNext == 1)
            {
                previousNode->pNextNode = nextNode;
            }
            else if(flagPrev == 1 && flagNext == 0)
            {
                previousNode->pNextNode = NULL;
            }
            else
            {
                this->pFirstNode = nextNode;
            }

            this->size--;
            pNode->pElement = NULL;
            //free((void*) pNode);

            returnAux = 0;
        }
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        for(int i = ll_len(this) - 1; i >= 0; i--)
        {
            ll_remove(this, i);
        }
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        free((void*) this);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* pNode = NULL;

    if(this != NULL)
    {
        for(int i = 0; i < ll_len(this); i++)
        {
            pNode = getNode(this, i);

            if(pNode->pElement == pElement)
            {
                returnAux = i;
                break;
            }
        }
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(ll_len(this) == 0)
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(index >= 0 && index <= ll_len(this))
        {
            addNode(this, index, pElement);
            returnAux = 0;
        }
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* pNode = NULL;

    if(this != NULL)
    {
        if(index >= 0 && index < ll_len(this))
        {
            pNode = getNode(this, index);
            returnAux = pNode->pElement;
            ll_remove(this, index);
        }
    }
    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int flagExiste = 0;

    if(this != NULL)
    {
        Node* pNode = (Node*)malloc(sizeof(Node*));

        for(int i = 0; i < ll_len(this); i++)
        {
            pNode = getNode(this, i);

            if(pNode->pElement == pElement)
            {
                flagExiste = 1;
                break;
            }
        }
        returnAux = flagExiste;
    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;

    if(this != NULL && this2 != NULL)
    {
        if(ll_len(this2) == 0)
        {
            returnAux = 0;
        }
        else
        {
            Node* pNode = (Node*)malloc(sizeof(Node*));

            for(int i = 0; i < ll_len(this2); i++)
            {
                pNode = getNode(this2, i);
                returnAux = ll_contains(this, pNode->pElement);

                if(returnAux == 0)
                {
                    break;
                }
            }
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL)
    {

        if(ll_len(this) == 0)
        {
            if(from == 0 && to > from)
            {
                cloneArray = ll_newLinkedList();
                Node* pNode = (Node*)malloc(sizeof(Node*));
                pNode = getNode(this, 0);
                ll_add(cloneArray, pNode->pElement);
            }
        }
        else if(from >= 0 && from < ll_len((this)))
        {
            if(to > from && to <= ll_len(this))
            {
                cloneArray = ll_newLinkedList();
                Node* pNode = (Node*)malloc(sizeof(Node*));

                for(int i = from; i < to; i++)
                {
                    pNode = getNode(this, i);
                    ll_add(cloneArray, pNode->pElement);
                }
            }
        }
    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL)
    {
        cloneArray = ll_subList(this, 0, ll_len(this));
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    int swapeo = 0;

    if(this != NULL && (*pFunc) != NULL && (order == 1 || order == 0))
    {
        if(ll_len(this) > 1)
        {
            Node* NodeA = (Node*)malloc(sizeof(Node*));
            Node* NodeB = (Node*)malloc(sizeof(Node*));
            void* EmployeeAux = (void*)malloc(sizeof(void*));

            for(int i = 0; i < ll_len(this) - 1; i++)
            {

                for(int j = i + 1; j < ll_len(this); j++)
                {
                    NodeA = getNode(this, i);
                    NodeB = getNode(this, j);

                    if(order == 0)
                    {
                        //DESCENDENTE
                        swapeo = pFunc((void*)NodeA->pElement, (void*)NodeB->pElement);

                        if(swapeo == -1)
                        {
                            EmployeeAux = NodeA->pElement;
                            ll_set(this, i, NodeB->pElement);
                            ll_set(this, j, EmployeeAux);
                        }
                    }
                    else
                    {
                        //ASCENDENTE
                        swapeo = pFunc((void*)NodeA->pElement, (void*)NodeB->pElement);

                        if(swapeo == 1)
                        {
                            EmployeeAux = NodeA->pElement;
                            ll_set(this, i, NodeB->pElement);
                            ll_set(this, j, EmployeeAux);
                        }

                    }
                }
            }
        }
        returnAux = 0;
    }
    return returnAux;
}

