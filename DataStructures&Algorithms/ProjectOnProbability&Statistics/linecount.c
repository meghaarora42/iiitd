#include<stdio.h>
#include<string.h>
void loc(char filename[]);
int main()
{
	char filename[20];
	printf("Enter file to calculate line of code-");
	gets(filename);
	loc(filename);
	return 0;
}
void loc(char filename[])
{
	
	FILE *data;
	char eachline[500];
	int total=0,badlines=0,i=0,k,currentline,flag=0;
	data=fopen(filename,"r");
	while(fgets(eachline,500,data)!=NULL)
	{
		total+=1;
		if (eachline[0]=='\n')//empty line
			badlines+=1;
		for(i=0;i<=strlen(eachline);i++)
		{
			if (((int)(eachline[i])!=42) &&((int)(eachline[i])!=47))
				break;//no comment in  line
			if (((int)eachline[i]==47)&&(((int)eachline[i+1]==42)||((int)eachline[i+1]==47)))
			{
				badlines+=1;//comment in line
				currentline=total;//commentline number stored
			}	
			if ((((int)eachline[i]==42)&&((int)eachline[i+1]==47))&&(total!=currentline))
			{                      //comment ends but not in that line
				for(k=i+2;k<strlen(eachline);k++)
				{                     //some code in same line as comment ended yes or no
					if (isalnum(eachline[k]))
						flag=1;
				}
				if(flag==1)
					break;//if yes its not a badline
				badlines+=1; // if no its a badline(only comment)
			}	
		}
	}
	printf("Total number of lines in the code are : %d \n",total-badlines);
	fclose(data);
}
