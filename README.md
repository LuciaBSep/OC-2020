# OC-2020
Proyecto Organizacion de Computadoras, Universidad Nacional del Sur

El objetivo principal del proyecto es implementar en lenguaje C un programa que registre la frecuencia de aparicion de palabras que forman parte de un archivo de texto.
Con este objetivo se den implementar:
 - TDA Lista, para almacenar elementos de tipo generico.
 - TDA Mapeo, para almacenar pares clave-valor de tipo generico.
 - Un programa principal, el cual implementa la dinamica de la aplicacion

# TDA Lista
Implementar un TDA Lista en lenguaje C, cuyos elementos sean punteros genericos. La lista debe ser implementada mediante una estructura simplemente enlazada con celda centinela, utilizando el concepto de posicion indirecta. La implementacion de la misma debe respetar la operaciones y estructuras definidas en el archivo lista.h

# TDA Mapeo
Implementar un TDA Mapeo en lenguaje C, cuyas claves y valores encapsulados sean punteros genericos. El mapeo debe ser implementado mediante una tabla hash abierta haciendo uso del TDA Lista. La implementacion del mismo debe respetar la operaciones y estructuras definidas en el archivo mapeo.h

# Programa Principal
Implementar una aplicacion de consola que, tomando como argumento por lınea de comandos el nombre de un archivo de texto, recorra el mismo y compute la cantidad de apariciones de las palabras que componen el archivo haciendo uso del TDA Mapeo. Una vez modelados estos datos estadısticos, la aplicacion debera ofrecer un menu de operaciones, que permita lo siguiente:

Cantidad apariciones: permite ingresar una palabra y muestra la cantidad de veces que dicha palabra se encuentra en el archivo.

Salir: permite finalizar el programa, pero antes de esto se encarga de liberar toda la memoria utilizada por los TDA Lista y TDA Mapeo.

El programa implementado, denominado evaluador, debe conformar la siguiente especificacion al ser invocado desde la lınea de comandos:
$ evaluador <archivo texto>
El parametro archivo texto indica el archivo a partir del cual se contabilizara la frecuencia de aparicion de las palabras que lo componen. A modo de simplificacion, asuma que el archivo de texto se compondra de caracteres ASCII basico unicamente, y que toda palabra en el mismo sera valida (no se requiere ningun tratamiento en particular sobre las secuencias de caracteres).
 
En cualquier caso, el programa principal debe finalizar retornando: 
- 0 en caso de finalizacion exitosa.
- -1 en caso de error al intentar la apertura del archivo parametrizado.
- -2 en caso de error ante la invocacion del programa.
- 
En caso de finalizacion erronea, ademas de codigo de retorno indicado, el programa debe mostrar por pantalla un mensaje indicando la naturaleza del error.
