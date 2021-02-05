#include <stdlib.h>
#include <stdio.h>
#include "lista.h"
#include "mapeo.h"

/**
 Inicializa una lista vacia.
 Una referencia a la lista creada es referenciada en *L.
 Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/

extern void crear_lista(tLista *l)
{
    (*l)=(tLista)malloc(sizeof(struct celda));
    if (l==NULL)
        exit(LST_ERROR_MEMORIA);
    (*l)->elemento=NULL;
    (*l)->siguiente=NULL;
}

/**
 Inserta el elemento E, en la posicion P, en L.
 Con L = A,B,C,D y la posicion P direccionando C, luego:
 L' = A,B,E,C,D.
 Finaliza indicando LST_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/

extern void l_insertar(tLista l, tPosicion p, tElemento e)
{
    struct celda *nueva_celda=(struct celda*)malloc(sizeof(struct celda));
    if (nueva_celda==NULL)
        exit(LST_ERROR_MEMORIA);
    if (p!=NULL)
    {
        if (l->siguiente!=NULL)
        {
                nueva_celda->elemento=e;
                nueva_celda->siguiente=p->siguiente;
                p->siguiente=nueva_celda;
        }
        else
        {
            nueva_celda->elemento=e;
            nueva_celda->siguiente=NULL;
            l->siguiente=nueva_celda;
        }

    }else {
        exit(LST_POSICION_INVALIDA);
    }
}

/**
 Elimina la celda P de L.
 El elemento almacenado en la posicion P es eliminado mediante la funcion fEliminar.
 Finaliza indicando LST_POSICION_INVALIDA si P es fin(L).
**/
extern void l_eliminar(tLista l, tPosicion p, void (*fEliminar)(tElemento))
{
    tPosicion posicion_auxiliar;
    if (p->siguiente==NULL)
        exit (LST_POSICION_INVALIDA);
    fEliminar(p->siguiente->elemento);
    posicion_auxiliar=p->siguiente->siguiente;
    free(p->siguiente);
    p->siguiente=posicion_auxiliar;
}

/**
 Destruye la lista L, elimininando cada una de sus celdas.
 Los elementos almacenados en las celdas son eliminados mediante la funcion fEliminar.
**/

extern void l_destruir(tLista * l, void (*fEliminar)(tElemento))
{
    tPosicion posicion=*l;
    tPosicion auxiliar;
    while (posicion->siguiente!=NULL)
    {
        fEliminar(posicion->elemento);
        auxiliar=posicion->siguiente;
        free(posicion);
        posicion=auxiliar;
    }
    fEliminar(posicion->elemento);
    free(posicion);
    *l=NULL;
}

 /**
 Recupera y retorna el elemento en la posicion P.
 Finaliza indicando LST_POSICION_INVALIDA si P es fin(L).
**/

extern tElemento l_recuperar(tLista l, tPosicion p)
{
    if (l==NULL)
        exit(LST_POSICION_INVALIDA);
    if ((p==NULL)||(p->siguiente==NULL))
        exit(LST_POSICION_INVALIDA);

    return (p->siguiente)->elemento;
}

/**
 Recupera y retorna la primera posicion de L.
 Si L es vacia, primera(L) = ultima(L) = fin(L).
**/

extern tPosicion l_primera(tLista l)
{
    if (l==NULL)
        exit(LST_POSICION_INVALIDA);
    tPosicion primera_posicion=l;

    return primera_posicion;
}

/**
 Recupera y retorna la posicion siguiente a P en L.
 Finaliza indicando LST_NO_EXISTE_SIGUIENTE si P es fin(L).
**/

extern tPosicion l_siguiente(tLista l, tPosicion p)
{
    if (p->siguiente==NULL)
        exit(LST_NO_EXISTE_SIGUIENTE);

    return p->siguiente;
}

/**
 Recupera y retorna la posicion anterior a P en L.
 Finaliza indicando LST_NO_EXISTE_ANTERIOR si P es primera(L).
**/

extern tPosicion l_anterior(tLista l, tPosicion p)
{
    tPosicion posicion=l;
    int encontre=0;
    if (posicion==p)
        exit(LST_NO_EXISTE_ANTERIOR);
    while (encontre==0 && posicion->siguiente!=NULL)
    {
        if (posicion->siguiente==p)
            encontre=1;
        else
            posicion=posicion->siguiente;
    }
    if (encontre!=0)
        return posicion;
    else
        return NULL;
}

/**
 Recupera y retorna la ultima posicion de L.
 Si L es vacia, primera(L) = ultima(L) = fin(L).
**/

extern tPosicion l_ultima(tLista l)
{
    tPosicion posicion=l;
    if (posicion->siguiente!=NULL)
    {
        while(posicion->siguiente->siguiente!=NULL)
        {
            posicion=posicion->siguiente;
        }
    }

    return posicion;
}

/**
 Recupera y retorna la posicion fin de L.
 Si L es vacia, primera(L) = ultima(L) = fin(L).
**/

extern tPosicion l_fin(tLista l)
{
    tPosicion posicion=l;
    if(posicion->siguiente!=NULL){
        while(posicion->siguiente!=NULL)
        {
            posicion=posicion->siguiente;
        }
    }

    return posicion;
}

/**
 Retorna la longitud actual de la lista.
**/

extern int l_longitud(tLista l)
{
    tPosicion posicion=l;
    int longitud=0;
    if(l->siguiente!=NULL)
    {
    while (posicion->siguiente!=NULL)
    {
        longitud=longitud+1;
        posicion=posicion->siguiente;
    }
    }

    return longitud;
}
