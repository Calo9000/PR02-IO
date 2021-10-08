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


int main()
{


	int i,j,n;
	float sum=0;
	printf("Enter the no. of keys:");
	scanf("%d",&n);
    
    float W[n][n],E[n][n],R[n][n],P[n];
	
    do
	{
		printf("\nEnter the probabilities of keys:");
		for(i=1;i<=n;i++)
		{
			scanf("%f",&P[i]);
			sum+=P[i];
		}
		if(sum==1)
			break;
		else
			printf("\nEnter the correct set of probabilities");
	}while(sum!=1);
	OptimalBST(n,W,E,R,P);
	printf("\n");
	for(i=1;i<=n;i++)
	{
		for(j=0;j<=n;j++)
		{
			printf("%.2f\t",E[i][j]);
		}
		printf("\n");
	}
    printf("\n");
    for(i=1;i<=n;i++)
	{
		for(j=0;j<=n;j++)
		{
			printf("%.2f\t",W[i][j]);
		}
		printf("\n");
	}
    printf("\n");
    for(i=1;i<=n;i++)
	{
		for(j=0;j<=n;j++)
		{
			printf("%.2f\t",R[i][j]);
		}
		printf("\n");
	}
	return 0;
}