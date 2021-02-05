#include <stdlib.h>
#include <stdio.h>
#include "mapeo.h"
#include "lista.h"


// ---------------------------------------------------------------------------------------------
// Definicion de prototipos y documentacion de las funciones.
// Obs.: la tabla hash debe mantener control del factor de carga en todo momento.
// Obs.: el factor de carga maximo permitido equivale al 75% de la longitud de la tabla.
// ---------------------------------------------------------------------------------------------

/**
    Funcion que busca el mayor numero entre a y b
**/

int MAX(int a, int b)
{
    if (a>b)
        return a;
    else
        return b;
}


/**
    ESTA FUNCION NO HACE NADA Y SE USA EN INSERTAR CUANDO HAY QUE AGRANDAR LA TABLA HASH.
    Se quiere borrar la lista vieja sin borrar las entradas que son copiadas a la lista nueva.
**/
void funcion_eliminar_entradas_vacia()
{
}


/**
    Funcion que elimina la entrada e
**/
void funcion_eliminar_entradas(tElemento e)
{
    tEntrada entrada=(tEntrada) e;
    free(entrada);
}


/**
 Inicializa un mapeo vacio, con capacidad inicial igual al MAX(10, CI).
 Una referencia al mapeo creado es referenciada en *M.
 A todo efecto, el valor hash para las claves sera computado mediante la funcion fHash.
 A todo efecto, la comparacion de claves se realizara mediante la funcion fComparacion.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/

extern void crear_mapeo(tMapeo * m, int ci, int (*fHash)(void *), int (*fComparacion)(void *, void *))
{
    (*m)=(tMapeo)malloc(sizeof(struct mapeo));
    if (*m==NULL)
        exit(MAP_ERROR_MEMORIA);
    int longitud_t=MAX(10,ci);
    (*m)->longitud_tabla=longitud_t;
    (*m)->cantidad_elementos = 0;
    (*m)->comparador=fComparacion;
    (*m)->hash_code=fHash;

    (*m)->tabla_hash=(tLista*)malloc(sizeof(tLista)*longitud_t);
    if ((*m)->tabla_hash==NULL)
        exit(MAP_ERROR_MEMORIA);

    for (int i=0;i!=longitud_t;i++)
    {
        crear_lista(&*((*m)->tabla_hash+i));
    }
}

/**
 Inserta una entrada con clave C y valor V, en M.
 Si una entrada con clave C y valor Vi ya existe en M, modifica Vi por V.
 Retorna NULL si la clave C no existia en M, o Vi en caso contrario.
 Finaliza indicando MAP_ERROR_MEMORIA si no es posible reservar memoria correspondientemente.
**/


extern tValor m_insertar(tMapeo m, tClave c, tValor v)
{
    int valor_hash,esta_la_clave,longitud_anterior,longitud_nueva,clave_nueva,longitud_lista;
    tValor valor_a_retornar=NULL;
    tEntrada entrada,entrada_anterior,entrada_nueva;
    tPosicion posicion_actual,posicion_ultima,posicion_lista_entradas;
    tLista lista;
    tClave clave_anterior;
    tLista *tabla_anterior=m->tabla_hash;

    if ((m->cantidad_elementos)+1>=(75*(m->longitud_tabla)/100))
    {
        longitud_anterior=m->longitud_tabla;
        longitud_nueva=longitud_anterior*2;
        m->longitud_tabla=longitud_nueva;
        m->tabla_hash=(tLista*)malloc(sizeof(tLista)*longitud_nueva);
        if (m->tabla_hash==NULL)
            exit(MAP_ERROR_MEMORIA);
        for(int i=0;i!=longitud_nueva;i++)
        {
            crear_lista(&*(m->tabla_hash+i));
        }

        for (int i=0;i!=longitud_anterior;i++)
        {
            lista=(*(tabla_anterior+i));
            longitud_lista=l_longitud(lista);

            //VEO SI LA LISTA DE ENTRADAS ANTERIOR NO ESTA VACIA
            if (longitud_lista!=0)
            {
                posicion_lista_entradas=l_primera(lista);
                for (int j=0;j!=longitud_lista;j++)
                {
                    entrada_anterior=(tEntrada)l_recuperar(lista,posicion_lista_entradas);
                    clave_anterior=entrada_anterior->clave;
                    clave_nueva=(m->hash_code(clave_anterior))%(m->longitud_tabla);
                    l_insertar(*(m->tabla_hash+clave_nueva),l_primera(*(m->tabla_hash+clave_nueva)),entrada_anterior);
                    posicion_lista_entradas=l_siguiente(lista,posicion_lista_entradas);
                }
            }
            l_destruir(&lista,&funcion_eliminar_entradas_vacia);
        }
    }

    valor_hash=(m->hash_code(c))%(m->longitud_tabla);

    lista=(*(m->tabla_hash+valor_hash));

    posicion_actual=l_primera(lista);

    posicion_ultima=l_fin(lista);
    esta_la_clave=0;

    while(esta_la_clave==0 && posicion_actual!=posicion_ultima)
    {
        entrada=(tEntrada)l_recuperar(lista,posicion_actual);
        if(m->comparador(entrada->clave,c)==0)
            {esta_la_clave=1;
            }
        else
           {
               posicion_actual=l_siguiente(lista,posicion_actual);
           }
    }

    if (esta_la_clave==1)
    {
        valor_a_retornar=entrada->valor;
        entrada->valor=v;
    }
    else
    {
        entrada_nueva=(tEntrada)malloc(sizeof(struct entrada));
        if (entrada_nueva==NULL)
            exit(MAP_ERROR_MEMORIA);
        m->cantidad_elementos=m->cantidad_elementos+1;
        entrada_nueva->clave=c;
        entrada_nueva->valor=v;
        l_insertar(lista,l_primera(lista),entrada_nueva);
    }

    return valor_a_retornar;

}

/**
 Elimina la entrada con clave C en M, si esta existe.
 La clave y el valor de la entrada son eliminados mediante las funciones fEliminarC y fEliminarV.
**/


extern void m_eliminar(tMapeo m, tClave c,  void (*fEliminarC)(void *), void (*fEliminarV)(void *))
{
	int valor_hash=(m->hash_code(c)%(m->longitud_tabla));
	int encontre_la_clave=0;
	tPosicion posicion_actual,posicion_ultima;
	tEntrada entrada_que_se_esta_viendo;

	tLista lista=(*(m->tabla_hash+valor_hash));
	posicion_actual=l_primera(lista);
	posicion_ultima=l_fin(lista);

	while (encontre_la_clave==0 && posicion_actual!=posicion_ultima)
	{
		entrada_que_se_esta_viendo=(tEntrada)l_recuperar(lista,posicion_actual);
		if (m->comparador(entrada_que_se_esta_viendo->clave,c)==0)
		{
			encontre_la_clave=1;
		}
		else
			posicion_actual=l_siguiente(lista,posicion_actual);
	}

	if (encontre_la_clave==1)
	{
		fEliminarC(entrada_que_se_esta_viendo->clave);
		fEliminarV(entrada_que_se_esta_viendo->valor);
		l_eliminar(lista,posicion_actual,&funcion_eliminar_entradas);
		m->cantidad_elementos=(m->cantidad_elementos)-1;
	}
}

/**
 Destruye el mapeo M, elimininando cada una de sus entradas.
 Las claves y valores almacenados en las entradas son eliminados mediante las funciones fEliminarC y fEliminarV.
**/
extern void m_destruir(tMapeo * m, void (*fEliminarC)(void *), void (*fEliminarV)(void *))
{
	tMapeo mapeo_auxiliar;
	int cantidad_elementos_arreglo,j,cant_elementos_lista;
	tEntrada entrada_a_eliminar;
	tLista lista_a_eliminar;

	mapeo_auxiliar=*m;
	cantidad_elementos_arreglo=mapeo_auxiliar->longitud_tabla;

	for(int i=0;i!=cantidad_elementos_arreglo;i++)
	{
		lista_a_eliminar=(*(mapeo_auxiliar->tabla_hash+i));

		if(lista_a_eliminar!=NULL)
		{
			j=0;
			cant_elementos_lista=l_longitud(lista_a_eliminar);
			while(j!=cant_elementos_lista)
			{
				entrada_a_eliminar=l_recuperar(lista_a_eliminar,l_primera(lista_a_eliminar));
				fEliminarC(entrada_a_eliminar->clave);
				fEliminarV(entrada_a_eliminar->valor);
				l_eliminar(lista_a_eliminar,l_primera(lista_a_eliminar),&funcion_eliminar_entradas);
				cant_elementos_lista=cant_elementos_lista-1;
			}
			l_destruir(&lista_a_eliminar,&funcion_eliminar_entradas_vacia);
		}
	}

    (*m)->cantidad_elementos=0;
    (*m)->longitud_tabla=0;
    (*m)->comparador=NULL;
    (*m)->hash_code=NULL;
    free((*m)->tabla_hash);
    (*m)->tabla_hash=NULL;
    free((*m));
    (*m)=NULL;

}


/**
 Recupera el valor correspondiente a la entrada con clave C en M, si esta existe.
 Retorna el valor correspondiente, o NULL en caso contrario.
**/


extern tValor m_recuperar(tMapeo m, tClave c)
{
	tValor valor_a_retornar;
	int valor_hash,encontre_la_entrada;
	tPosicion posicion_lista_entradas,ultima_posicion;
	tEntrada entrada_que_se_esta_viendo;
	tLista lista;

	valor_a_retornar=NULL;
	valor_hash=(m->hash_code(c))%(m->longitud_tabla);
	lista=(*(m->tabla_hash+valor_hash));

	if (l_longitud(lista)>0)
	{
		encontre_la_entrada=0;
		posicion_lista_entradas=l_primera(lista);
		ultima_posicion=l_fin(lista);

		while (encontre_la_entrada==0 && posicion_lista_entradas!=ultima_posicion)
		{
		  entrada_que_se_esta_viendo=(tEntrada)l_recuperar(lista,posicion_lista_entradas);
			if (m->comparador(entrada_que_se_esta_viendo->clave,c)==0)
			{
				encontre_la_entrada=1;
				valor_a_retornar=entrada_que_se_esta_viendo->valor;
			}
			else
			{
				posicion_lista_entradas=l_siguiente((tLista)lista,posicion_lista_entradas);
			}
		}

	}
	return valor_a_retornar;
}


