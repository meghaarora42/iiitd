#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>

/************************************
Matrix multiplication: Z=X*Y
Pitch used to represent 2D array as 1D i.e.
Matrix[i][j] is stored as array  Matrix[i*Pitch + j]
************************************/

void mat_mult(int size,int Xpitch, const double X[],int Ypitch, const double Y[],int Zpitch, double Z[])
{
    int i,j,k;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            double sum = 0.0;
            for (k = 0; k < size; k++)
            {
                sum += X[i*Xpitch + k]*Y[k*Ypitch + j];
                Z[i*Zpitch + j] = sum;
            }
        }
    }
}

void mat_add(int size,int Xpitch, const double X[],int Ypitch, const double Y[],int Spitch, double S[])
{
    int i,j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            S[i*Spitch + j] = X[i*Xpitch + j] + Y[i*Ypitch + j];
        }
    }
}

void mat_sub(int size,int Xpitch, const double X[],int Ypitch, const double Y[],int Spitch, double S[])
{
    int i,j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            S[i*Spitch + j] = X[i*Xpitch + j] - Y[i*Ypitch + j];
        }
    }
}

void strassen(int size,int Xpitch, const double X[],int Ypitch, const double Y[],int Zpitch, double Z[])
{
    if (size <= 4)   //base case of 4X4 matrices which uses simple matrix multiplication
    {
        mat_mult(size, Xpitch, X, Ypitch, Y, Zpitch, Z);
        return;
    }
    const int size_sub = size/2;      //size of sub-matrices

    const double *A = X;    // sub matrices from X
    const double *B = X + size_sub;
    const double *C = X + size_sub*Xpitch;
    const double *D = C + size_sub;

    const double *E = Y;    // sub-matrices from Y
    const double *F = Y + size_sub;
    const double *G = Y + size_sub*Ypitch;
    const double *H = G + size_sub;

    double *P[7];   // array of pointers
    int i;
    for (i = 0; i < 7; i++)
    {
        P[i] = (double *) malloc(size_sub*size_sub*sizeof(double));
    }
    double *temp1 = (double *) malloc(size_sub*size_sub*sizeof(double));
    double *temp2 = (double *) malloc(size_sub*size_sub*sizeof(double));

    mat_sub(size_sub, Ypitch, F, Ypitch, H, size_sub, temp1);      // P0 = A*(F - H);
    strassen(size_sub, Xpitch, A, size_sub, temp1, size_sub, P[0]);  //recursive calls

    mat_add(size_sub, Xpitch, A, Xpitch, B, size_sub, temp1);    // P1 = (A + B)*H
    strassen(size_sub, size_sub, temp1, Ypitch, H, size_sub, P[1]);

    mat_add(size_sub, Xpitch, C, Xpitch, D, size_sub, temp1);    // P2 = (C + D)*E
    strassen(size_sub, size_sub, temp1, Ypitch, E, size_sub, P[2]);

    mat_sub(size_sub, Ypitch, G, Ypitch, E, size_sub, temp1);     // P3 = D*(G - E);
    strassen(size_sub, Xpitch, D, size_sub, temp1, size_sub, P[3]);

    mat_add(size_sub, Xpitch, A, Xpitch, D, size_sub, temp1);    // P4 = (A + D)*(E + H)
    mat_add(size_sub, Ypitch, E, Ypitch, H, size_sub, temp2);
    strassen(size_sub, size_sub, temp1, size_sub, temp2, size_sub, P[4]);

    mat_sub(size_sub, Xpitch, B, Xpitch, D, size_sub, temp1);    // P5 = (B - D)*(G + H)
    mat_add(size_sub, Ypitch, G, Ypitch, H, size_sub, temp2);
    strassen(size_sub, size_sub, temp1, size_sub, temp2, size_sub, P[5]);

    mat_sub(size_sub, Xpitch, A, Xpitch, C, size_sub, temp1);     // P6 = (A - C)*(E + F)
    mat_add(size_sub, Ypitch, E, Ypitch, F, size_sub, temp2);
    strassen(size_sub, size_sub, temp1, size_sub, temp2, size_sub, P[6]);

    //sub matrices of Z(result matrix)

    mat_add(size_sub, size_sub, P[4], size_sub, P[3], size_sub, temp1);// Z11 = (P3 + P4) + (P5 - P1)
    mat_sub(size_sub, size_sub, P[5], size_sub, P[1], size_sub, temp2);
    mat_add(size_sub, size_sub, temp1, size_sub, temp2, Zpitch, Z);

    mat_add(size_sub, size_sub, P[0], size_sub, P[1], Zpitch, Z + size_sub);// Z12 = P0 + P1

    mat_add(size_sub, size_sub, P[2], size_sub, P[3], Zpitch, Z + size_sub*Zpitch); // Z21 = P2 + P3

    mat_add(size_sub,size_sub, P[0], size_sub, P[4], size_sub, temp1);    // Z22 = (P0 + P4) - (P2 + P6)
    mat_add(size_sub, size_sub, P[2], size_sub, P[6], size_sub, temp2);
    mat_sub(size_sub, size_sub, temp1, size_sub,temp2 , Zpitch, Z + size_sub*(Zpitch + 1));

    free(temp2);  //deallocation of temporary matrices
    free(temp1);
    for (i = 6; i >= 0; i--)
    {
        free(P[i]);      //deallocation of array pointers
    }
}

void mat_print(int size, int pitch, const double Mat[])
{
    int i,j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
           printf("%+0.4f ", Mat[i*pitch + j]);
        }
        printf("\n");
    }
}

void mat_rand(int size, int pitch, double Mat[])  // randomly generate a size x size matrix
{
    int i,j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            Mat[i*pitch + j] = (double)(rand()%50);
        }
    }
}

int main()
{
    int size;
    double *X, *Y, *Z;
    printf("Enter size of matrices to be generated randomly : ");
    scanf("%d",&size);
    X = (double*) malloc(size*size*sizeof(double));
    Y = (double*) malloc(size*size*sizeof(double));
    Z = (double*) malloc(size*size*sizeof(double));
    mat_rand(size, size, X);
    mat_rand(size, size, Y);
    mat_rand(size, size, Z);
    printf("\n");
    printf("Matrix 1 : \n");
    printf("\n");
    mat_print(size, size, X);
    printf("\n");
    printf("Matrix 2 : \n");
    printf("\n");
    mat_print(size, size, Y);
    printf("\n");
    printf("Resultant Matrix : \n");
    printf("\n");
    strassen(size, size, X, size, Y, size, Z);
    mat_print(size, size, Z);


  return 0;
}
