# Taller de Programación I - Cátedra Veiga - FIUBA
# Trabajo Práctico 0


## Introducción

Este es el primer trabajo de la materia Taller de Programación I. Tiene como objetivo nivelar los conocimientos de C y familiarizarnos con la plataforma de registros y corrección automática de trabajos SERCOM. En el siguiente se explicarán tanto las preguntas planteadas en la consigna, como el código dado y las salidas del SERCOM al interactuar con este. En cada paso se explicará la evolución de los archivos dados por la cátedra con la finalidad de acostumbrarse al sistema de entregas y a la dinámica del curso. 

## PASO 0: Entorno de Trabajo

### a) Output del programa "main.c" sin y con valgrind respectivamente. 

```
niyoζ:~/Taller-de-Programacion-9508/tp0$ gcc main.c -o tp
niyoζ:~/Taller-de-Programacion-9508/tp0$ ./tp
Hola mundo!
niyoζ:~/Taller-de-Programacion-9508/tp0$ valgrind ./tp
==7545== Memcheck, a memory error detector
==7545== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==7545== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==7545== Command: ./tp
==7545==
Hola mundo!
==7545==
==7545== HEAP SUMMARY:
==7545==     in use at exit: 0 bytes in 0 blocks
==7545==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
==7545==
==7545== All heap blocks were freed -- no leaks are possible
==7545==
==7545== For lists of detected and suppressed errors, rerun with: -s
==7545== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

### b) Utilidades de Valgrind y opciones más comunes.

***Valgrind*** es un software cuya finalidad está mayoritariamente en facilitar el debugging de un programa, permitiéndote saber cuando tenés pérdidas de memoria en tu código o rastrear facilmente variables no inicializadas, entre otros casos.

Un típico ejemplo donde ***Valgrind*** puede ser muy útil, es cuando usamos memoria dinámica y nos estamos olvidando de liberarla. Si tuvieramos fugas de memoria en el heap, esto estaría indicado en lo que vemos por salida estándar.

En el ejemplo antes dado vemos el mensaje ```All heap blocks were freed -- no leaks are possible``` lo que significa que no estamos dejando memoria en el heap sin liberar.

Las opciones más comunes de este son:
- ```--leak-check=full``` especifica por la salida estándar del programa todas las pérdidas de memoria que haya tenido el programa
- ```--track-origins=yes``` muestra el origen de las variables no inicializadas
- ```--track-fds=yes``` muestra que archivos quedaron abiertos
- ```--show-reachable=yes``` muestra que bloques de memoria no liberados aun son alcanzables.  

### c) Función ***sizeof()***

La función ***sizeof()*** recibe una variable y devuelve el tamaño del mismo en bytes. El valor que devuelve depende de cada arquitectura. En el caso de ***sizeof(char)*** el resultado es 1 ya que codificamos todo caracter con 8 bits y luego ***sizeof(int)*** es 4. Pero en casos como ***sizeof(void*)*** puede ocurrir que si estamos en una arquitectura de 32 bits el resultado sea 4 y en 64 bits el resultado sea 8 (es decir, la cantidad de bits necesarios para representar un puntero cambió entre arquitecturas). 

### d) ***Sizeof() meets structs***

Sea el siguiente ejemplo de código en C en una arquitectura x86 de 64 bits:

```
struct tp0{
	char c;
	void* ptr;
};
``` 

Si tomamos ```sizeof(struct tp0)``` veremos que el resultado será de 16. Esto es ya que el offset del ```char c``` es de 0 y ocupa 1 byte, haciendo que ```void* ptr``` tenga que empezar con offset 1 en el struct, pero esto no ocurre ya que esta posición de memoria no sería múltiplo de su tamaño (es decir, no es múltiplo de 8). En consecuencia el compilador agrega 7 bytes extras entre los elementos del struct). Demostrando así que el valor esperado no es ```sizeof(char) + sizeof(void*)```. 

Queda entonces demostrado que no siempre ocurre que el ```sizeof(struct s)``` es igual al ```sizeof(s1) + sizeof(s2) + ... + sizeof(sn) ``` (es decir, a la suma de sus elementos). Esto ocurre por el padding.

### e) STDIN, STDOUT y STDERR

Estos 3 archivos son la entrada estándar de datos, salida estándar de datos y salida de errores respectivamente.Son archivos que, dentro de los sistemas operativos UNIX, permanecen abiertos por cada proceso para comunicar información, ya sea entre procesos o hacia el usuario. 

También se puede concatenar estas salidas y entradas. Por ejemplo, si ejecuto en la términal ```ls > archivos.txt``` estaría escribiendo en mi archivo ***archivos.txt*** un listado de todos los documentos, programas y directorios que tenga almacenado en mi posición actual. Si en cambio ejecuto ```cat < archivos.txt``` estaría haciendo que el ejecutable de la izquiera reciba una lista de archivos por stdin y finalmente los imprima. También tengo al pipe que concatena el stdout del ejecutable izquierdo con el stdin del ejecutable del lado derecho del mismo. Por ejemplo si ejecuto ```cat archivos.txt | grep .txt ``` estaría conectando lo que lanza por stdout el término izquierdo (que sería una lista de los documentos del directorio donde estoy parado) al stdin del término derecho (que recibe mi lista de documentos y escribe por stdout los que tienen ".txt" en el nombre).

## PASO 1

#### Desempaquetando y compilando el codigo...

```
Descomprimiendo el codigo 'source_unsafe.zip'...
Archive:  source_unsafe.zip
  inflating: source_unsafe/paso1_main.c
  inflating: source_unsafe/paso1_wordscounter.c
  inflating: source_unsafe/paso1_wordscounter.h
Compilando el codigo...
  CC  paso1_main.o
paso1_main.c: In function ‘main’:
paso1_main.c:22:9: error: unknown type name ‘wordscounter_t’
   22 |         wordscounter_t counter;
      |         ^~~~~~~~~~~~~~
paso1_main.c:23:9: error: implicit declaration of function ‘wordscounter_create’ [-Wimplicit-function-declaration]
   23 |         wordscounter_create(&counter);
      |         ^~~~~~~~~~~~~~~~~~~
paso1_main.c:24:9: error: implicit declaration of function ‘wordscounter_process’ [-Wimplicit-function-declaration]
   24 |         wordscounter_process(&counter, input);
      |         ^~~~~~~~~~~~~~~~~~~~
paso1_main.c:25:24: error: implicit declaration of function ‘wordscounter_get_words’ [-Wimplicit-function-declaration]
   25 |         size_t words = wordscounter_get_words(&counter);
      |                        ^~~~~~~~~~~~~~~~~~~~~~
paso1_main.c:27:9: error: implicit declaration of function ‘wordscounter_destroy’ [-Wimplicit-function-declaration]
   27 |         wordscounter_destroy(&counter);
      |         ^~~~~~~~~~~~~~~~~~~~
make: *** [<builtin>: paso1_main.o] Error 1

real    0m0.032s
user    0m0.019s
sys     0m0.005s
[Error] Fallo la compilacion del codigo en 'source_unsafe.zip'. Codigo de error 2
```

Aquí la función main está intentando usar tipos no declarados y genera un error de compilación. Todas estas declaraciones faltantes se encuentran en el archivo ```paso1_wordscounter.h```. Es por eso que en la linea 22 el compilador no reconoce el tipo y en las lineas 23, 24, 25 y 27 no se reconocen las llamadas a las funciones no incluidas. 

#### Verificando el codigo...

```
/task/student//source_unsafe/paso1_wordscounter.c:27:  Missing space before ( in while(  [whitespace/parens] [5]
/task/student//source_unsafe/paso1_wordscounter.c:41:  Mismatching spaces inside () in if  [whitespace/parens] [5]
/task/student//source_unsafe/paso1_wordscounter.c:41:  Should have zero or one spaces inside ( and ) in if  [whitespace/parens] [5]
/task/student//source_unsafe/paso1_wordscounter.c:47:  An else should appear on the same line as the preceding }  [whitespace/newline] [4]
/task/student//source_unsafe/paso1_wordscounter.c:47:  If an else has a brace on one side, it should have it on both  [readability/braces] [5]
/task/student//source_unsafe/paso1_wordscounter.c:48:  Missing space before ( in if(  [whitespace/parens] [5]
/task/student//source_unsafe/paso1_wordscounter.c:53:  Extra space before last semicolon. If this should be an empty statement, use {} instead.  [whitespace/semicolon] [5]
/task/student//source_unsafe/paso1_wordscounter.h:5:  Lines should be <= 80 characters long  [whitespace/line_length] [2]
/task/student//source_unsafe/paso1_main.c:12:  Almost always, snprintf is better than strcpy  [runtime/printf] [4]
/task/student//source_unsafe/paso1_main.c:15:  An else should appear on the same line as the preceding }  [whitespace/newline] [4]
/task/student//source_unsafe/paso1_main.c:15:  If an else has a brace on one side, it should have it on both  [readability/braces] [5]
Done processing /task/student//source_unsafe/paso1_wordscounter.c
Done processing /task/student//source_unsafe/paso1_wordscounter.h
Done processing /task/student//source_unsafe/paso1_main.c
Total errors found: 11
```

Yendo en orden comentaré los 11 errores mencionados: 
- Dentro del archivo ```paso1_wordscounter.c```, linea 27, no se está dejando un espacio entre el while y su condición. 
- Luego, en el if de la linea 41 hay 2 espacios extras del lado izquierdo. Dentro de la misma linea ocurre que solamente puede haber hasta un espacio (continuo) dentro de la condición. 
- En la línea 47 no ocurre que el else if arranca donde la condición anterior termina, sino que se va una línea para abajo; las llaves deberían estar en la misma línea.
- En la línea 48 no hay un espacio entre el paréntesis y el if.
- En la línea 53 hay un espacio extra entre el "next_state" y el punto y coma. 
- Luego en el archivo ```paso1_wordscounter.h``` se advierte que las líneas no deben tener más de 80 caracteres. 
- Finalmente en ```paso1_main.c``` ocurre que en la línea 12 se está usando la función insegura ```strcpy()``` y recomienda usar snprintf (como se dijo en clase, strcpy es insegura ya que no sabe que tamaño tiene el buffer de destino, cosa que puede hacer que pisemos memoria que no nos corresponde). 
- Finalmente en la línea 15 vemos que el else debería empezar donde termina la llave anterior y que las llaves deberían estar en la misma línea. 

#### Finalizando...

```
El despaquetado y/o compilacion finalizo con un codigo de error (1). Tendras que arreglar esto antes de poder continuar.
```

El Makefile que se usa para este proyecto tiene los flags: ```CFLAGS = -Wall -Werror -pedantic -pedantic-errors``` y particularmente el flag ```-Werror``` ***transforma todos los warnings en errors.***


