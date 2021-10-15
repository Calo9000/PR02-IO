#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bstpd.h"
#include "bstgreedy.h"
#include <locale.h>
#define N 100
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
    
    /*
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

    */
    //prueba(c, valor, peso, n);
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
                //experimento(a);
                printf("Ejecutando modo de experimento\n");
            } else printf("Ingrese un número entero mayor que 0\n");
    }else{
		printf("Argumentos inválidos\n\tIngrese -X si desea ejecutar el modo de ejemplo\n\tIngrese -E=n si desea ejecutar el modo experimento, donde n es un número entero mayor que 0\n");
    }
	
    return 0;
}