#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapeo.h"
#include "lista.h"
#define letras (caracteres[i]>=97 && caracteres[i]<=122)


/**
    Funcion que elimina la clave que le pasan como parametro,
    en este caso se trata de caracteres.
**/
void funcion_eliminar_claves_evaluador(char *palabra)
{
    free(palabra);
}

/**
    Funcion que elimina el valor que le pasan como parametro,
    en este caso se trata de un entero.
**/
void funcion_eliminar_valores_evaluador(int *valor)
{
    free(valor);
}


/**
    Funcion para comparar dos claves, las claves en este caso son caracteres.
    El comparador retorna 0 si las dos claves son IGUALES.
**/

int comparacion_claves_evaluador(char* palabra1, char* palabra2)
{

    int i = 0;
    if (strlen(palabra1)==strlen(palabra2)){
        while ((*((palabra1+i))!='\0') && (*((palabra2+i))!='\0') && (*(palabra1+i)==*(palabra2+i)))
              i=i+1;
        if (*(palabra1+i)!='\0' && *(palabra2+i)!='\0')
            return 1;
        else return 0;
    }else return 1;

}

/**
    Funcion hash que convierte los caracteres en un entero.
**/

int funcion_hash_evaluador(char *palabra)
{
    long hash = 5381;
    int c;

    while ((c = *palabra++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}


int ingreso_nro_de_operacion()
{
    int nro_operacion;
    int nro_valido=0;
    printf("Ingrese el n%cmero de operacion que desea realizar: ",163);
    while (!nro_valido)
    {

        if(scanf("%i",&nro_operacion) != 1 )
        {
            printf("No ingreso un n%cmero, ingrese un n%cmero de operaci%cn: ",163,163,162);
            /*limpio buffer*/
            while(getchar() != '\n');
        }
        else
        {
            if(nro_operacion<1 || nro_operacion>2)
            {
                printf("No ingreso un n%cmero valido, ingrese nuevamente un n%cmero de operaci%cn: ",163,163,162);
            }
            else
            {
                nro_valido=1;
            }
        }
    }
    return nro_operacion;
}

/**
    Funcion que permite salir del programa, liberando toda la memoria ocupada.
**/

void salir(tMapeo mapeo)
{
    m_destruir(&mapeo,(void*)&funcion_eliminar_claves_evaluador,(void*)&funcion_eliminar_valores_evaluador);
    printf("Operaci%cn realizada con exito\n",162);
    exit(0);
}

/**
    Funcion que permite al usuario ingresar la palabra que quiere buscar en el archivo y muestra si esta
    presente o no, y en caso de estarlo la cantidad de veces que aparece.
**/

void mostrar_palabra(tMapeo map){

    char palabra[20];
    int *valor;
    printf("# Operacion 1 : Buscar palabra en el archivo #\n");
    printf("Ingrese una palabra para chequear si esta en el archivo: \n");
    scanf("%s",palabra);

    valor=(int*)m_recuperar(map,palabra);
    if (valor==NULL || valor==0){
        printf("La palabra no se encuentra en el texto. \n");
    }
    else
    {
        if ((*valor)>1)
            printf("La palabra %s se encuentra %d veces en el texto. \n",palabra,*valor);
        else
            printf("La palabra %s se encuentra 1 vez en el texto. \n",palabra);
    }
}

/**
    Funcion que permite elegir al usuario la operacion que desea realizar.
**/


void operaciones(tMapeo map)
{
    int nro_operacion;
    printf("%cQu%c operaci%cn desea realizar ahora? \n",168,130,162);
    nro_operacion = ingreso_nro_de_operacion();
    switch(nro_operacion)
    {
    case 1:
        mostrar_palabra(map);
        operaciones(map);
        break;
    case 2:
        salir(map);
        break;
    }
}


void menu_operaciones(FILE* archivo_texto)
{
	tMapeo mapeo;
	char* caracteres;
	char palabra[20];
	char* palabra_a_insertar;
	int i,j, longitud;
	int* valor;
	int* valor_recuperado;

	crear_mapeo(&mapeo,20,(void*)&funcion_hash_evaluador,(void*)&comparacion_claves_evaluador);
	caracteres=(char*)malloc(sizeof(char)*100);

	while (feof(archivo_texto)==0)
	{
		fgets(caracteres,100,archivo_texto);
        longitud=strlen(caracteres); //longitud del renglon
        j=0;

        for (i=0; i<=longitud; i++) //leo todo el renglon en busca de caracteres no validos
        {
            if (letras)  //si es una letra armo una palabra
            {
                //estoy dentro de una palabra.
                palabra[j]=caracteres[i];
                j++;
                //le asigno fin de palabra, aunque no haya llegado al final
            }
            else   //si es un separador, puedo haber terminado de armar la palabra
            {
                palabra[j]='\0';
				int l = strlen(palabra);
				if (l>0)   // si longitud de palabra es mayor a 0 arme una cadena
                {
                    valor_recuperado=(int*)m_recuperar(mapeo,palabra);
                    if (valor_recuperado==NULL || valor_recuperado==0)
                    {
                        valor=(int*)malloc(sizeof(int));
						palabra_a_insertar=(char*)malloc(sizeof(char)*20);
                        strcpy(palabra_a_insertar,palabra);
                        *valor=1;
                        m_insertar(mapeo,palabra_a_insertar,valor);
                    }
				else
					{
						*valor_recuperado=*valor_recuperado+1;
						m_insertar(mapeo,palabra,valor_recuperado);
					}
					j=0;
				}
			}
		}
	}

	fclose(archivo_texto); //cierro archivo, ya no lo uso
	free(caracteres);

    if(&(mapeo)->cantidad_elementos > 0)
    {
        printf("Men%c de operaciones:\n",163);
        printf("1- Cantidad de apariciones\n");
        printf("2- Salir: permite salir del programa\n");
        operaciones(mapeo);
    }
    else
        printf("El archivo no contiene palabras v%clidas.\n",160);
}



int main(int argc, char *argv[])
{
    char* nombre_archivo_texto;
    FILE* archivo_texto;

    printf("##### EVALUADOR DE ARCHIVO DE TEXTO #####\n");
    if(argc==2)
    {
        nombre_archivo_texto = argv[1];
        if((archivo_texto= fopen(nombre_archivo_texto,"r"))==NULL)
        {
            /*Abro el archivo en modo lectura*/
            printf ("Error al intentar la apertura del archivo.\n");
            return -1;
        }
        else
        {
            menu_operaciones(archivo_texto);
        }
    }
    else
    {
        printf ("Error ante la invocaci%cn del programa\n",162);
        return -2;
    }
    return 0;

}
