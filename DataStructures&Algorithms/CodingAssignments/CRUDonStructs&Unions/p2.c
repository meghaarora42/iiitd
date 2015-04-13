#include<stdio.h>
#include<string.h>
#include<stdlib.h>

union part {
    int partnumber;
    char name[80];
    int quantity;
} array1[100],array2[100],array3[100];

int part_count=0,partnum,i;

void printop()
    {
        printf("Part number\tPart name\tQuantity on hand\n");
        for(i=0;i<part_count;i++)
        {
        printf("%d            \t%s          \t%d\n",array1[i].partnumber,array2[i].name,array3[i].quantity);
        }
    }

void searchop()
    {
        int fail=1;
        printf("Enter partnumber: ");
        scanf("%d",&partnum);
        for(i=0;i<part_count;i++)
          {
                if(array1[i].partnumber==partnum)
                {
                    printf("Partnumber:%d\nName:%s\nQuantity on hand:%d",array1[i].partnumber,array2[i].name,array3[i].quantity);
                    fail=0;
                    break;
                }
          }
        if (fail==1)
            printf("Part not in inventory.");
    }

void updateop()
    {
        int quantitychange;
        int fail=1;
        printf("Enter partnumber:");
        scanf("%d",&partnum);
        for(i=0;i<part_count;i++)
        {
            if(array1[i].partnumber==partnum)
                {
                    fail=0;
                    printf("Enter change in quantity on hand:");
                    scanf("%d",&quantitychange);
                    array3[i].quantity+=quantitychange;
                    printf("New records:");
                    printf("Partnumber:%d\nName:%s\nQuantity on hand:%d",array1[i].partnumber,array2[i].name,array3[i].quantity);
                    break;
                }
        }
        if (fail==1)
            printf("Part not in inventory.");
    }

void insertop()
    {
        printf("Enter part name:");
        fgetc(stdin);//to send empty line to buffer
        fgets((array2[part_count].name),80,stdin);
        printf("Enter partnumber:");
        scanf("%d",&array1[part_count].partnumber);
        printf("Enter quantity on hand:");
        scanf("%d",&array3[part_count].quantity);
        part_count++;
    }
    
int main()
{
    char option;
    int escape=0;
    array1[0].partnumber=1;   //One data record hard coded.
    strcpy(array2[0].name,"Screw Driver");
    array3[0].quantity=42;

    part_count++;
    printf("Operation Codes:\ni for insert\ns for serach\nu for update\np for print\nq for quit" );
    while(escape!=1)
    {
        printf("\nEnter opertaion to be performed: ");
        scanf(" %c",&option);
        switch(option)
        {
            case 'p':
            {
                printop();
                break;
            }
            case 's':
            {
                searchop();
                break;
            }
            case 'i':
            {
                insertop();
                break;
            }
            case 'u':
            {
                updateop();
                break;
            }
            case 'q':
            {
                escape=1;
                break;
            }
            default:
            {
                printf("Only i,s,q,p and u inputs allowed!");
            }

        }

    }
}
