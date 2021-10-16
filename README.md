# PR02-IO
ACERCA DEL PROYECTO:
El proyecto consiste en un programa que resolverá el Problema de los Árboles Binarios de Búsqueda Óptimos (A.B.B)
usando la Programación Dinámica junto con una versión Greedy del Algoritmo.

      -Algoritmo de Programación Dinámica
      -Algoritmo Greedy


En el cual se ejecutarán en 2 principales ejecuciones: modo ejemplo y modo experimento.
La elaboración de este proyecto fue realizada en el lenguaje de programación C en un sistema operativo Linux.

INSTRUCCIONES DE UTILIZACIÓN:
1) Para compilar el programa se debe ingresar a la terminal dentro de la carpeta del proyecto. 
   1) a) Antes de compilar/ejecutar el programa es importante instalar pdfLatex para poder visualizar el PDF resultante,
         para esto se debe ingresar el siguiente comando dentro de la terminal que se abrió: sudo apt-get install texlive-latex-base.
2) Dentro de la terminal se debe ingresar el comando "make".
3) Existen varias opciones al momento de iniciar el programa, se puede correr el programa con los siguientes formatos: 

      `./bst -X`

   - Donde la primera ejecución corresponde al modo ejemplo del programa en el cuál se resolverá un solo caso aleatorio
   con los 2 algoritmos mencionados.

      `./bst -E=n`

   - Donde n corresponde al número de casos diferentes que se resolverán en cada escenario con los 2 algoritmos mencionados.

4) a) Si se ejecuta el primer comando (./bst -X) dentro de la terminal, el programa despliegará el siguiente output dentro de un archivo PDF:
------------
      -Una breve descripción del problema, en el que se contempla las llaves utilizadas y la probabilidad de cada una. Además de los algoritmos que se utilizaron.
      -Los datos generados para el problema, esto se detalla en una tabla  con las llaves utilizadas y la probabilidad generada aleatoriamente para cada una.
      
      -Se muestra tanto la matriz A como la matriz R para poder encontrar el árbol óptimo con el algoritmo de Programación Dinámica, a su vez se incluye el tiempo de ejecución medido para este algoritmo. Y en última
      instancia se muestra el árbol generado por el algoritmo de programación dinámica .
	-Se muestra tanto la matriz A como la matriz R para poder encontrar el árbol óptimo con el algoritmo Greedy, a su vez se incluye el tiempo de ejecución medido para este algoritmo. Y en última
      instancia se muestra el árbol generado por el algoritmo Greedy.


	IMPORTANTE: El PDF así como el archivo .tex que se usó para generarlo se guardan en la carpeta del proyecto con el nombre de output.pdf y output.tex respectivamente.
------------
      
     

4) b) Si se ejecuta el segundo comando (/bst -E=n) dentro de la terminal, el programa desplegará un documento PDF con 3 tablas en donde:
------------
      -La descripción del problema, y una breve descripción de cada una de las tablas que se van a mostrar en el documento.
      
      -Una primera tabla en la que se detalla los tiempos promedios de ejecución con el algoritmo de Programación Dinámica, al lado izquierdo se tiene la cantiad de llaves 
      utilizada y a la derecha de la tabla se tiene el tiempo promedio en segundos.
	-Una segunda tabla en la que se detalla los tiempos promedios de ejecución con el algoritmo Greedy, al lado izquierdo se tiene la cantiad de llaves 
      utilizada y a la derecha de la tabla se tiene el tiempo promedio en segundos.
      -Una tercera tabla en la que se detalla los porcentajes de éxitos en los que el algortimo Greedy alcanza el mismo resultado que el de Programación Dinámica según
      la cantidad de llaves utilizada.

	IMPORTANTE: El PDF así como el archivo .tex que se usó para generarlo se guardan en la carpeta del proyecto con el nombre de ejemplo.pdf y ejemplo.tex respectivamente.
------------
