#include<bits/stdc++.h>
using namespace std;

#define MAX 30	 // Number of unknowns
double mat[MAX][MAX];
int N;
void print()
{
	for (int i=0; i<N; i++, printf("\n"))
		for (int j=0; j<=N; j++)
			printf("%lf ", mat[i][j]);
	printf("\n");
}
void swap_row(int i, int j)
{
	for (int k=0; k<=N; k++)
	{
		double temp = mat[i][k];
		mat[i][k] = mat[j][k];
		mat[j][k] = temp;
	}
}
int forwardElim()
{
	for (int k=0; k<N; k++)
	{
		int i_max = k;
		int v_max = mat[i_max][k];
		for (int i = k+1; i < N; i++)
			if (abs(mat[i][k]) > v_max)
				v_max = mat[i][k], i_max = i;
		if (!mat[k][i_max])
			return k;
		if (i_max != k)
			swap_row(k, i_max);
		for (int i=k+1; i<N; i++)
		{
			double f = mat[i][k]/mat[k][k];
			for (int j=k+1; j<=N; j++)
				mat[i][j] -= mat[k][j]*f;
			mat[i][k] = 0;
		}
		print();
		
	}
	return -1;
}
void backSub()
{
	double x[N];
	for (int i = N-1; i >= 0; i--)
	{
		x[i] = mat[i][N];
    	for (int j=i+1; j<N; j++)
		{
		    x[i] -= mat[i][j]*x[j];
		}
		x[i] = x[i]/mat[i][i];
	}

	printf("\nSolution for the system:\n");
	for (int i=0; i<N; i++)
		printf("%lf\n", x[i]);
}
void gaussianElimination()
{
	int singular_flag = forwardElim();
	if (singular_flag != -1)
	{
		if (mat[singular_flag][N])
			printf("Inconsistent System.");
		else
			printf("May have infinitely many "
				"solutions.");
		return;
	}
	print();
	backSub();
}


int main()
{
	cin>>N;
	for(int i=0;i<N;i++)
		for(int j=0;j<N+1;j++)
			cin>>mat[i][j];

	gaussianElimination();
	return 0;
}

