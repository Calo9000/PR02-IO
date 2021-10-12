#include<stdio.h>
#include<stdlib.h>
#define N 100
#define inf 9999

// inicializa y rellena las matrices root y average. n es cantidad de llaves, p es un arreglo con la probabilidad de cada llave ordenado segun prioridad
void bstPD(int n, float p[N],  int R[N][N], float A[N][N])
{
	

	for(int i=0;i<n+1;i++){
		for(int j = 0; j<n+1; j++){
			R[i][j]=0;
			A[i][j]=0;
		}
	}


	for(int j = 0; j<n+1;j++){
		for(int ii = 0; ii<n+1; ii++){
			int i = n-ii;
			if(i==j){
				A[i][j] = 0;
			}
			else if(j==(i+1)){
				A[i][j] = p[i];
				R[i][j] = i+1;
			}
			else if(j>(i+1)){
				float B[n];
				float c = 0;
				float m = inf;
				for(int k = i; k<j; k++){
					c+=p[k];
				}
				for(int k = i; k<j; k++){
					float x = A[i][k]+A[k+1][j]+c;
					if(m>x){
						m = x;
						R[i][j] = k+1;
					}
				}
				A[i][j] = m;
			}
		}
	}

}