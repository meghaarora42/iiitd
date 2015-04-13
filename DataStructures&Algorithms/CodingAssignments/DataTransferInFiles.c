#include<stdio.h>

void cpfunction(char inputfile[40], char outputfile[40]);

int main()
{
	char cpfile[40],psfile[40];
	printf("Enter the file to copy from: ");
	gets(cpfile);
	printf("Enter the file to copy to: ");
	gets(psfile);
	cpfunction(cpfile,psfile);
	return 0;
}

void cpfunction(char inputfile[40], char outputfile[40])
{
	FILE *cp,*ps;
	char data;
	cp=fopen(inputfile,"r");
	ps=fopen(outputfile,"a");
	while(42)
	{
		data=fgetc(cp);
		if(data==EOF)
			break;
		else
			fputc(data,ps);
	}
	fclose(cp);
	fclose(ps);
}
