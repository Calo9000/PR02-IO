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
    v[0] = (char) valor[raiz];

    printf("valor: %c\n", (char) valor[raiz]);

    strncat(subarbol, v, 1);
    strcat(subarbol, "}\n");
    if(raiz==i){
        printf("%d, %d, %d\n", i, j, raiz);
        strcat(subarbol, "child[missing]\n");
        strcat(subarbol, "child{node{\n");
        v[0] = (char) valor[j];
        strncat(subarbol, v, 1);
        strcat(subarbol, "}}\n");
        strcat(arbol, subarbol);
        return;
    }
    else if(raiz==j){
        printf("%d, %d, %d\n", i, j, raiz);
        strcat(subarbol, "child{node{\n");
        v[0] = (char) valor[j];
        strncat(subarbol, v, 1);
        strcat(subarbol, "}}\n");
        strcat(subarbol, "child[missing]\n");
        strcat(arbol, subarbol);
        return;
    }
    else{
        printf("%d, %d: %d\n", i, j, raiz);
        strcat(subarbol, "child {\n");
        agregarNodo(R, arbol, i, raiz-1, valor);
        strcat(subarbol, "}\nchild {");
        agregarNodo(R, arbol, raiz+1, j, valor);
        strcat(subarbol, "}");
        strcat(arbol, subarbol);
        return;
    }
}

int ejemplo(){

	// cantidad de objetos
	int n = 6;
    printf("Cantidad de objetos: %d\n",n);


    // valor de los objetos
	char valor[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
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
    
    
    char arbolPD[ARRAY_SIZE] = "\\begin{figure}[ht]\n\\centering\n\\begin{tikzpicture}[\nevery node/.style = {minimum width = 3em, draw, circle},\n]\n\\scriptsize\n\\";

    agregarNodo(R_pd, arbolPD, 1, 6, valor);

    printf("%s\n",arbolPD);

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