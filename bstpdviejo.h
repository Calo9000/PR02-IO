#include<stdio.h>
#include<stdlib.h>
#define N 100
#define inf 9999


void bstPD(int n, float W[N][N], float A[N][N], float R[N][N], float P[N])
{
	int i,j,r,l;
	float q;
	for(i=1;i<=n+1;i++){
		A[i][i-1]=0;
		W[i][i-1]=0;
	}

	for(l=1;l<=n;l++){
		for(i=1;i<=(n-l+1);i++){
			j=i+l-1;
			W[i][j]=W[i][j-1]+P[j];
			A[i][j]=inf;
			for(r=i;r<=j;r++){
				q=A[i][r-1]+A[r+1][j]+W[i][j];
				if(q<A[i][j]){
					A[i][j]=q;
					R[i][j]=r;
				}
			}
		}
	}
}

