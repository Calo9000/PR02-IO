#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "bstpd.h"
#include "bstgreedy.h"
#include <locale.h>
#define N 100

int ejemplo(){

	// cantidad de objetos
	int n = 6;
    printf("Cantidad de objetos: %d\n",n);


    // valor de los objetos
	char valor[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	float p[n];
    float s = 0;
	for (int i = 0; i<n; i++){
		// probabilidad de los objetos
		p[i] = rand() % 100 + 1;
        s+=p[i];
	}
    for (int i = 0; i<n; i++){
		// probabilidad de los objetos
		p[i] = p[i]/s;
		printf("Objeto %d-> Valor: %c, Probabilidad: %.4f\n", i, valor[i], p[i]);
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