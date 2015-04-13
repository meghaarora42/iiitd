#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

void rand_data(float *ptr,int size)
{
    int i;
    for(i=0;i<size;i++)
    {
        *(ptr+i)=(float)rand()/(float)(RAND_MAX/100);
    }
}
void file_data(float *ptr, int size)
{
    int i=0;
    char filename[20];
    char ch;
    printf("Enter file name to read data from : \n");
    scanf("%s",filename);
    printf("Reading data....\n");
    FILE *fp = fopen(filename,"r");
    if( fp == NULL )
    {
      printf("Error while opening the file.\n");
      exit(1);
    }

   printf("The contents of %s file are :\n", filename);

   while(!feof(fp))
   {   
	fscanf(fp,"%f",(ptr+i));	
	i++;
   }
	
    fclose(fp);
    printf("Data successfully read from file.\n");
}
void display_data(float *ptr,int size)
{
    int i;
    printf("Data : \n");
    for(i=0;i<size;i++)
    {
        printf("%.1f  ",*(ptr+i));
    }
}
