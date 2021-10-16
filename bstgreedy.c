#include<stdio.h>
#include<stdlib.h>
#define N 100
#define inf 9999

// retorna el indice del mayor numero en un arreglo
int max(float p[], int n){
	int t; 
	t=0;
	for(int i=1; i<n; i++){
		if(p[i]>p[t]) t = i;
	}
	return t;
}

// n es cantidad de llaves, p es probabilidad de las llaves de acuerdo al orden de prioridad, r es arreglo raiz que se modifica
void bstGreedy(int n, float p[N],  int R[N][N])
{
	

	for(int i=0;i<n+1;i++){
		for(int j = 0; j<n+1; j++){
			R[i][j]=0;
		}
	}

	for(int i=1; i<n+1; i++){
		for(int j=0; j<n+1; j++){
			if(j>0 && i<=j){
				int s = j-i+1;
				float T[s];
				printf("%d, %d\n", i, j);
				for(int k= 0; k<=j-i; k++){
					T[k] = p[i+k-1];
					printf("%.2f ", T[k]);
				}
				printf("\ns: %d ", s);
				printf("MAX: %d ", max(T,s));
				R[i-1][j] = max(T,s)+i;
				printf("\n");
			}
		}
	}


}


int main()
{

	//int n = 5;
	int n = 10;
	
	//float p[] = {0.3, 0.2, 0.1, 0.15, 0.25};
	float p[] = {1,2,3,4,5,6,7,8,9,10};

	//	EL ORDEN DE LAS PROBABILIDADES ES EL ORDEN DE PRIORIDAD DE LAS LLAVES


	int R[N][N];

	bstGreedy(n, p, R);
	

	printf("\n");
	for(int i=0;i<n+1;i++){
		for(int j = 0; j<n+1; j++){
			printf("%d\t",R[i][j]);
		}
		printf("\n");
	}



	return 0;
}