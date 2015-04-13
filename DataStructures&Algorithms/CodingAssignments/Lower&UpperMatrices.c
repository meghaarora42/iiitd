#include<stdio.h>
#include<stdlib.h>
void lower(int n)
{	int matrix[n][n],i,j;
	for(i=0;i<n;i++)
	
	{

	   for(j=0;j<n;j++)
           {
		if(i<j)
		{
			matrix[i][j]=0;   }
		else
       			matrix[i][j]=rand() % 50;   
	   }
	}
	printf("Maximum number of non zero elements = %d \n",(((n*(n+1))/2)));
	for(i=0;i<n;i++)
	{	for(j=0;j<n;j++)
		{
			if(i>=j)
				printf("element[%d][%d]=%d \n",i,j,matrix[i][j]);
		}
	}
}
void upper(int n)
{	int matrix[n][n],i,j;
	for(i=0;i<n;i++)
	{    for(j=0;j<n;j++)
	     {
		if(i>j)
			matrix[i][j]=0;
		else
			matrix[i][j]=rand() % 50;
	     }
	}
	printf("Maximum number of non zero elements = %d \n",(((n*(n+1))/2)));
	for(i=0;i<n;i++)
	{    for(j=0;j<n;j++)
	     {
		if(i<=j)
			printf("element[%d][%d]=%d \n",i,j,matrix[i][j]);
	      }
	}
}
void s_lower(int n)
{	int matrix[n][n],i,j;
	for(i=0;i<n;i++)
	{    for(j=0;j<n;j++)
	     {
		if(i<=j)
			matrix[i][j]=0;
		else
			matrix[i][j]=rand() % 50;
	     }
	}
	printf("Maximum number of non zero elements = %d \n",(((n*(n+1))/2)-n));
	for(i=0;i<n;i++)
	{    for(j=0;j<n;j++)
	     {
		if(i>j)
			printf("element[%d][%d]=%d \n",i,j,matrix[i][j]);
	     }	
	}
}
int main()
{
	int size,type;
	printf("Enter order of matrix: ");
	scanf("%d",&size);
	printf("Enter matrix type: 1-lower,2-upper,3-strictly lower : ");
	scanf("%d",&type);
	if(type==1)
		lower(size);
	if(type==2)
		upper(size);
	if(type==3)
		s_lower(size);
	return 0;
}
