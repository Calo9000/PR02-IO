#include<stdio.h>
#include<stdlib.h>
#define N 500
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
				for(int k= 0; k<=j-i; k++){
					T[k] = p[i+k-1];
				}
				R[i-1][j] = max(T,s)+i;
			}
		}
	}


}