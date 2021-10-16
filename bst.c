#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bstpd.h"
#include "bstgreedy.h"
#include <locale.h>
#define ARRAY_SIZE 5000

void agregarNodo(int R[N][N], char arbol[ARRAY_SIZE], int i, int j, char valor[6]){
    //printf("%d, %d\n",i, j);

    int raiz = R[i-1][j];
    char subarbol[ARRAY_SIZE] = "node {";
    char v[1];
    v[0] = (char) valor[raiz-1];

    //printf("valor: %c\n", (char) valor[raiz-1]);

    strncat(subarbol, v, 1);
    strcat(subarbol, "}\n");
    if (i==j){
        strcat(arbol, subarbol);
        return;
    }
    else if(raiz==i){
        //printf("%d, %d, %d\n", i, j, raiz);
        strcat(subarbol, "child[missing]\n");
        strcat(subarbol, "child{\n");
        strcat(arbol, subarbol);
        agregarNodo(R, arbol, raiz+1, j, valor);
        /*
        v[0] = (char) valor[j];
        strncat(subarbol, v, 1);
        strcat(subarbol, "}}\n");
        */
        strcat(arbol, "}\n");
        return;
    }
    else if(raiz==j){
        //printf("%d, %d, %d\n", i, j, raiz);
        strcat(subarbol, "child{\n");
        strcat(arbol, subarbol);
        agregarNodo(R, arbol, i, raiz-1, valor);
        strcat(arbol, "}\n");
        /*
        v[0] = (char) valor[j];
        strncat(subarbol, v, 1);
        strcat(subarbol, "}}\n");
        */
        strcat(arbol, "child[missing]\n");
        return;
    }
    
    else{
        //printf("%d, %d: %d\n", i, j, raiz);
        strcat(subarbol, "child {\n");
        strcat(arbol, subarbol);
        agregarNodo(R, arbol, i, raiz-1, valor);
        strcat(arbol, "}\nchild {");
        agregarNodo(R, arbol, raiz+1, j, valor);
        strcat(arbol, "}");
        return;
    }
}

int ejemplo(){

	// cantidad de objetos
	int n = 6;
    printf("Cantidad de objetos: %d\n",n);


    // valor de los objetos
	char valor[] = {'A', 'B', 'C', 'D', 'E', 'F'};
	float p[n];
    float s = 0;
	/*
    for (int i = 0; i<n; i++){
		// probabilidad de los objetos
		p[i] = rand() % 100 + 1;
        s+=p[i];
	}
    */

    float r = 0; 
    for (int k = 1; k<3; k++){
        p[2+(k-1)*3] = 0.16;
        for (int i = 0; i<2; i++){
            r = rand() % 17;
            r -= 9;
            r /= 100;
            p[(i)+2*(k-1)+(k-1)] = 0.17 + r;
            p[3*k-1] -= r;
        }
    }


    for (int i = 0; i<n; i++){
		// probabilidad de los objetos
		//p[i] = p[i]/s;
		printf("Objeto %d-> Valor: %c, Probabilidad: %.2f\n", i, valor[i], p[i]);
	}

    



    float A[N][N];
    int R_pd[N][N], R_greedy[N][N];

    clock_t begin = clock();
    bstPD(n, p, R_pd, A);
    clock_t end = clock();
    double d_pd = (double) (end - begin) / CLOCKS_PER_SEC;

    printf("\n");
	for(int i=0;i<n+1;i++){
		for(int j = 0; j<n+1; j++){
			printf("%d\t",R_pd[i][j]);
		}
		printf("\n");
	}

    printf("\n");
	for(int i=0;i<n+1;i++){
		for(int j = 0; j<n+1; j++){
			printf("%.2f\t",A[i][j]);
		}
		printf("\n");
	}

    printf("Tiempo de ejecución: %f\n", d_pd);
    printf("\n");
    begin = clock();
    bstGreedy(n, p, R_greedy);
    end = clock();

    printf("\n");
	for(int i=0;i<n+1;i++){
		for(int j = 0; j<n+1; j++){
			printf("%d\t",R_greedy[i][j]);
		}
		printf("\n");
	}

    double d_gr = (double) (end - begin) / CLOCKS_PER_SEC;
    printf("Tiempo de ejecución: %f\n", d_gr);
    printf("\n");
    
    
    char arbolPD[ARRAY_SIZE] = "\\begin{figure}[ht]\n\\centering\n\\begin{tikzpicture}[\nevery node/.style = {minimum width = 3em, draw, circle},\nlevel/.style={sibling distance={3cm/max(1,#1)}}\n]\n\\scriptsize\n\\";

    agregarNodo(R_pd, arbolPD, 1, 6, valor);

    //printf("%s\n",arbolPD);

    strcat(arbolPD, ";\n\\end{tikzpicture}\n\\caption{\\'Arbol generado por el algoritmo de programación din\\'amica}\n\\label{pd}\n\\end{figure}\n");

    char arbolGreedy[ARRAY_SIZE] = "\\begin{figure}[ht]\n\\centering\n\\begin{tikzpicture}[\nevery node/.style = {minimum width = 3em, draw, circle},\nlevel/.style={sibling distance={3cm/max(1,#1)}}\n]\n\\scriptsize\n\\";

    agregarNodo(R_greedy, arbolGreedy, 1, 6, valor);

    //printf("%s\n",arbolGreedy);

    strcat(arbolGreedy, ";\n\\end{tikzpicture}\n\\caption{\\'Arbol generado por el algoritmo greedy}\n\\label{greedy}\n\\end{figure}\n");

    char inicio[ARRAY_SIZE] = "\\documentclass{article}\n\\usepackage{fancyhdr}\n\\usepackage{caption}\n\\usepackage{tikz}\n\\usepackage{slashbox}\n\\pagestyle{fancy}\n\\lhead{Modo ejemplo}\n\\rhead{Proyecto II IC6400}\n\\begin{document}\n\\section*{Resultados del modo de ejemplo}\n\\subsection*{I. Descripción del problema}\nSe tienen 6 llaves diferentes (A, B, C, D, E y F), cada una de las cuales tiene una probabilidad diferente de ser buscada. El objetivo es construir un \\'arbol de b\\'usqueda binario a partir de estas llaves, de forma que el tiempo de b\\'usqueda promedio sea el menor posible. Para esto se emple\\'o un algoritmo de programaci\\'on din\\'amica y un algoritmo greedy.\n\n\\subsection*{II. Datos del problema}\nLos datos utilizados se resumen en la siguiente tabla:\n\n";

    char tablaDatos[ARRAY_SIZE] = "\\begin{table}[ht]\n\\centering\n\\begin{tabular}{r|l|l|l|l|l|l}\nLlave & A & B & C & D & E & F  \\\\\\hline\nProbabilidad";

    for(int i = 0; i<6; i++){
        char c[32];


        snprintf(c, 32, "%.2f", p[i]);

        strcat(tablaDatos, " & ");
        strcat(tablaDatos, c);
    }

    strcat(tablaDatos, "\n\\end{tabular}\n\\label{datos}\n\\end{table}\n\n");

    // inicio de seccion de programacion dinamica
    char pd[ARRAY_SIZE] = "\\subsection*{III. Programación Dinámica}\nA continuaci\\'on se muestran las tablas generadas por el algoritmo de programaci\\'on din\\'amica para encontrar el \\'arbol \\'optimo. Adem\\'as, se muestra el \\'arbol resultante.\n";
    
    // variable de tiempo de ejecucion
    char tiempoPD[32];
    snprintf(tiempoPD, 32, "%f", d_pd);

    // se añade el tiempo de ejecucion
    strcat(pd, "\nTiempo de ejecución: ");
    strcat(pd, tiempoPD);
    strcat(pd, " segundos.\n");

    strcat(pd, "\\begin{table}[ht]\n\\centering\n\\begin{tabular}{c|ccccccc}\n\\backslashbox{$i$}{$j$} & 0 & 1    & 2    & 3    & 4    & 5    & 6    \\\\ \\hline\n");



    for(int i = 0; i<7; i++){
        for(int j = -1; j<7; j++){
            if(j==-1){
                char c[32];
                snprintf(c, 32, "%d ", i+1);
                strcat(pd, c);
            }
            else if(i>j){
                strcat(pd, "& ");
            }
            else{
                strcat(pd, "& ");
                char c[32];
                snprintf(c, 32, "%.2f ", A[i][j]);
                strcat(pd, c);
            }
        }
        strcat(pd, "\\\\\n");
    }
    strcat(pd, "\n\\end{tabular}\n\\caption{Matriz A generada por el algoritmo de programación din\\'amica}\n\\label{A}\n\\end{table}\n\n");
    
    strcat(pd, "\\begin{table}[ht]\n\\centering\n\\begin{tabular}{c|cccccc}\n\\backslashbox{$i$}{$j$} & 1    & 2    & 3    & 4    & 5    & 6    \\\\ \\hline\n");

    // se rellena la tabla r
    for(int i = 0; i<6; i++){
        for(int j = 0; j<7; j++){
            if(j==0){
                char c[32];
                snprintf(c, 32, "%d ", i+1);
                strcat(pd, c);
            }
            else if(i>=j){
                strcat(pd, "& ");
            }
            else{
                strcat(pd, "& ");
                char c[32];
                snprintf(c, 32, "%d ", R_pd[i][j]);
                strcat(pd, c);
            }
        }
        strcat(pd, "\\\\\n");
    }

    // se finaliza la tabla r
    strcat(pd, "\n\\end{tabular}\n\\caption{Matriz R generada por el algoritmo de programación din\\'amica}\n\\label{R}\n\\end{table}\n\n");



    // inicio de seccion de algoritmo greedy
    char greedy[ARRAY_SIZE] = "\n\\newpage\n\\subsection*{IV. Algoritmo Greedy}\nA continuaci\\'on se muestran la tabla R generada por el algoritmo greedy. Adem\\'as, se muestra el \\'arbol resultante.\n";
    
    // variable de tiempo de ejecucion
    char tiempoGreedy[32];
    snprintf(tiempoGreedy, 32, "%f", d_gr);

    // se añade el tiempo de ejecucion
    strcat(greedy, "\nTiempo de ejecución: ");
    strcat(greedy, tiempoGreedy);
    strcat(greedy, " segundos.\n");

    strcat(greedy, "\\begin{table}[ht]\n\\centering\n\\begin{tabular}{c|cccccc}\n\\backslashbox{$i$}{$j$} & 1    & 2    & 3    & 4    & 5    & 6    \\\\ \\hline\n");



    // se rellena la tabla r
    for(int i = 0; i<6; i++){
        for(int j = 0; j<7; j++){
            if(j==0){
                char c[32];
                snprintf(c, 32, "%d ", i+1);
                strcat(greedy, c);
            }
            else if(i>=j){
                strcat(greedy, "& ");
            }
            else{
                strcat(greedy, "& ");
                char c[32];
                snprintf(c, 32, "%d ", R_greedy[i][j]);
                strcat(greedy, c);
            }
        }
        strcat(greedy, "\\\\\n");
    }
    // finalizar tabla r
    strcat(greedy, "\n\\end{tabular}\n\\caption{Matriz R generada por el algoritmo greedy}\n\\label{Rg}\n\\end{table}\n\n");

    char final[ARRAY_SIZE] = "\\end{document}";

    char documentoEj[ARRAY_SIZE] = "";

    strcat(documentoEj,inicio);
    strcat(documentoEj,tablaDatos);
    strcat(documentoEj,pd);
    strcat(documentoEj,arbolPD);
    strcat(documentoEj,greedy);
    strcat(documentoEj,arbolGreedy);
    strcat(documentoEj,final);

    printf("%s\n",documentoEj);
    
    
    char name[15] = "ejemplo";
    char fileName[70];
	char pdfName[70];


    snprintf(fileName, 90, "./%s.tex", name);
	snprintf(pdfName, 90, "%s.pdf", name);
    FILE *file;

    file = fopen(fileName, "w");
	fprintf(file, "%s\n", documentoEj);
	fclose(file);

    char pdflatexFile[90];
	char evinceFile[90];

    snprintf(pdflatexFile, 90, "pdflatex %s", fileName);

	snprintf(evinceFile, 90, "evince -s %s", pdfName);
						     
	system(pdflatexFile);
						        
	system(evinceFile);

    
   
    //prueba(c, valor, peso, n);
    return 0;

}

int experimento(int n){

    float promedios_pd[10], promedios_g[10];
    float porcentajes_g[10];

    for(int i = 0; i<10; i++){
        float tiempos_pd[n], tiempos_g[n];
        int coincidencias = 0;
        for(int k = 0; k<n; k++){
            // cantidad de llaves
            int c = (i+1)*10;

            // probabilidades
            float p[c];
            float s = 0;
            for(int a = 0; a<c; a++){
                p[a] = rand() % 1000;
                s+= p[a];
            }
            for(int a = 0; a<c; a++){
                p[a] = p[a]/s;
            }

            struct timespec start, end;

            float A[N][N];
            int Rpd[N][N], Rg[N][N];

            // se ejecuta el algoritmo con pd y se mide el tiempo
            clock_gettime(CLOCK_REALTIME, &start);
            bstPD(c, p, Rpd, A);
            clock_gettime(CLOCK_REALTIME, &end);
            double d_pd = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
            tiempos_pd[k] = d_pd;


            // se ejecuta el algoritmo greedy y se mide el tiempo
            clock_gettime(CLOCK_REALTIME, &start);
            bstGreedy(c, p, Rg);
            clock_gettime(CLOCK_REALTIME, &end);
            double d_g = (end.tv_sec-start.tv_sec)+(end.tv_nsec-start.tv_nsec)/1000000000.0;
            tiempos_g[k] = d_g;
        
            
            // fijarse si los arboles son iguales
            int sonIguales = 1;
            for(int x = 0; x<c; x++){
                for(int y = 1; y<c+1; y++){
                    if(Rpd[x][y] != Rg[x][y]){
                        sonIguales = 0;
                        goto fin;
                    }
                }
            }

            fin:

            coincidencias += sonIguales;

        }
        //SACAR LOS PROMEDIOS
        float total_pd = 0.0, total_g = 0.0;

        for (int a = 0; a<n; a++){
            total_pd += tiempos_pd[a];
            total_g += tiempos_g[a];
        }

        float pr_pd = total_pd/(float)n;
        float pr_g = total_g/(float)n;

        promedios_pd[i] = pr_pd;
        promedios_g[i] = pr_g;

        //printf("promedio pd %f \tpromedio gr %f\n", pr_pd, pr_g);


        // sacar porcentajes

        porcentajes_g[i] = (float) coincidencias * 100.0f / (float) n;

    }

    // generar el latex

    for(int i=0; i<10; i++){
        printf("%f\t", promedios_pd[i]);
    }
    printf("\n");
    for(int i=0; i<10; i++){
        printf("%f\t", promedios_g[i]);
    }
    printf("\n");
    for(int i=0; i<10; i++){
        printf("%f\t", porcentajes_g[i]);
    }
    printf("\n");


    // iniciar documento
    char archivo[ARRAY_SIZE] = "";

    char inicio[ARRAY_SIZE] = "\\documentclass{article}\n\\usepackage{textcomp}\n\\usepackage{tabularx}\n\\usepackage{fancyhdr}\n\\usepackage{multirow}\n\\usepackage{graphicx}\n\\usepackage{caption}\n\\pagestyle{fancy}\n\\lhead{Resultados de los algoritmos}\n\\rhead{Proyecto II IC6400}\n\\begin{document}\n\\section*{Reporte de resultados obtenidos}\nEn el presente documento se muestran los resultados de la ejecución de los algoritmos. Las tablas 1, 2 y 3 corresponden con los algoritmos de programación din\\'amica, greedy y greedy proporcional respectivamente. En cada casilla se muestra el tiempo de ejecución promedio de ";

    char entrada[10];    
    snprintf(entrada, 10, "%d", n);
    strcat(inicio, entrada);

    strcat(inicio, " escenarios. La cantidad de llaves que se ordenaron en cada escenario se muestra en la columna izquierda, y el tiempo en segundos se muestra en la columna derecha. \n En la tabla 3 se muestra el porcentaje de veces que el \\'arbol generado por el algoritmo greedy coincidi\\'o con el \\'arbol \\'optimo.\n\\begin{center}\n");

    // finalizar documento
    char final[ARRAY_SIZE] = "\\end{center}\n\\end{document}";


    // GENERAR LAS 3 TABLAS
    char inicioTabla[ARRAY_SIZE] = "\\begin{table}[ht]\n\\centering\n";

    char tituloPD[ARRAY_SIZE] = "\\caption*{Tabla 1: Tiempos promedio de ejecuci\\'on con Programaci\\'on Din\\'amica (\\textmu s)}\n\\label{1}\n";
    char tituloG[ARRAY_SIZE] = "\\caption*{Tabla 2: Tiempos promedio de ejecuci\\'on con Algoritmo Greedy (\\textmu s)}\n\\label{2}\n";
    char tituloGP[ARRAY_SIZE] = "\\caption*{Tabla 3: Porcentaje de \\'exitos para el algoritmo Greedy}\n\\label{4}\n";

    char inicioTabla2[ARRAY_SIZE] = "\\begin{tabular}{r|l}\nLlaves & \\begin{tabular}[c]{@{}c@{}}Tiempo\\\\ (segundos)\\end{tabular} \\\\ \\hline";

    // declarar tablas
    char tablaPD[ARRAY_SIZE] = "";
    char tablaG[ARRAY_SIZE] = "";
    char tablaGP[ARRAY_SIZE] = "";

    // preparar las tablas
    strcat(tablaPD, inicioTabla);
    strcat(tablaPD, tituloPD);
    strcat(tablaPD, inicioTabla2);

    strcat(tablaG, inicioTabla);
    strcat(tablaG, tituloG);
    strcat(tablaG, inicioTabla2);

    strcat(tablaGP, inicioTabla);
    strcat(tablaGP, tituloGP);
    strcat(tablaGP, inicioTabla2);

    return 0;

}



int main(int argc, char* argv[]){

    // generar números aleatorios
    time_t t;
    srand((unsigned) time(&t));

    if(argc != 2){
		printf("Argumentos inválidos\n\tIngrese -X si desea ejecutar el modo de ejemplo\n\tIngrese -E=n si desea ejecutar el modo experimento, donde n es un número entero mayor que 0\n");
		exit(0);
	}else if(strcmp(argv[1], "-X")==0){
            printf("Ejecutando modo de ejemplo\n");
            ejemplo();
    }else if(argv[1][0]=='-' && argv[1][1]=='E' && argv[1][2]=='='){
            char* c = argv[1]+3;
		    int a = atoi(c);
            //printf("%d\n", a);
            if (a>0) {
                printf("Ejecutando modo de experimento\n");
                experimento(a);

            } else printf("Ingrese un número entero mayor que 0\n");
    }else{
		printf("Argumentos inválidos\n\tIngrese -X si desea ejecutar el modo de ejemplo\n\tIngrese -E=n si desea ejecutar el modo experimento, donde n es un número entero mayor que 0\n");
    }
	
    return 0;
}