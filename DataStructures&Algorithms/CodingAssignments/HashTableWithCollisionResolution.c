#include <stdio.h>
#include <stdlib.h>
#include <string.h>
# define SIZE 10

typedef struct linked_list
{
    int identity;
    char name[40];
    struct linked_list *next;
    struct linked_list *pre;
} LL;

typedef struct arr
{
    struct linked_list *ptr;
} ARR;

struct arr record[SIZE];

void insert(int iden)
{
    int key;
    key=getkey(iden);
    //printf("%d",key);
    if(record[key].ptr==NULL)   ///first record in key
    {
        //printf("First entry being recorded.");
        LL *temp=(LL*)malloc(sizeof(LL));
        temp->identity=iden;
        printf("Enter the name: ");
        scanf("%s",&temp->name);
        temp->next=NULL;
        temp->pre=NULL;
        record[key].ptr=temp;
    }
    else
    {
        //printf("Entering record..");
        LL *temp=(LL*)malloc(sizeof(LL));
        temp->identity=iden;
        printf("Enter the name: ");
        scanf("%s",&temp->name);
        temp->pre=NULL;
        temp->next = record[key].ptr;
        temp->next->pre=temp;
        record[key].ptr=temp;
    }

}
void display()
{
    int i,j=0;
    printf("\nRecords : \n");
    for(i=0;i<SIZE;i++)
    {
        printf("%d",i);
        LL *temp=(LL*)malloc(sizeof(LL));
        temp=record[i].ptr;
        if(temp==NULL)
        {
            printf(" empty");
        }
        else
        {
            while(temp!= NULL)
            {
                printf(" -> [ %d ## %s ]",temp->identity,temp->name);
                temp=temp->next;
            }
        }
        printf("\n");
    }
    printf("\n");

}
void search(int iden)
{
    int key;
    key=getkey(iden);
    //printf("%d",key);
    LL *temp=(LL*)malloc(sizeof(LL));
    temp=record[key].ptr;
    if(temp==NULL)
    {
        printf("Record not found.\n");
    }
    else
    {
            int flag=0;
            while(1)
            {
                if(temp->identity==iden)
                {
                    printf("Record found.\n");
                    printf("NAME : %s\n",temp->name);
                    flag=1; ///record found
                    break;
                }
                else if(flag!=1 && temp->next != NULL)
                {
                    temp=temp->next;
                }
                else if(temp->next == NULL && flag == 0)
                {
                    printf("Record not found.\n");
                    break;
                }
            }
    }
}
void delete(int iden)
{
    int key;
    key=getkey(iden);
    //printf("%d",key);
    LL *temp=(LL*)malloc(sizeof(LL));
    temp=record[key].ptr;
    if(temp==NULL)
    {
        printf("Record not found.\n");
    }
    else
    {
            while(1)
            {
                if(temp->identity==iden)
                {
                    if(temp->pre==NULL && temp->next==NULL)
                    {

                        record[key].ptr=NULL;
                        free(temp);
                    }
                    else if(temp->pre==NULL)
                    {
                      record[key].ptr=temp->next;
                      free(temp);
                    }
                    else if(temp->next==NULL)
                    {
                        temp->pre->next=NULL;
                        free(temp);
                    }
                    else
                    {
                        temp->pre->next=temp->next;
                        temp->next->pre=temp->pre;
                        free(temp);
                    }

                    break;
                }
                else
                {
                    temp=temp->next;
                }
            }
    }

}
int getkey(int iden)
{
    return (iden % SIZE);
}
int main(void)
{
    int i,choice;
    int iden=0;
    printf("\n");
    printf("HASH TABLE with Collision Resolution(CHAINING)\n");
    printf("\n");
    printf("****************************************************\n");
    printf("\n");
    for(i=0;i<SIZE;i++)
    {
        record[i].ptr=NULL;
    }


    while(1)
    {
    printf("To enter record,press 1.\n");
    printf("To display records,press 2.\n");
    printf("To search for a record,press 3.\n");
    printf("To delete for a record,press 4.\n");
    printf("To exit,press 5.\n");
    printf("\n");
    printf("Enter choice : ");
    scanf(" %d",&choice);
    switch(choice)
    {
        case 1 :
            {
                printf("Enter unique identity number : ");
                scanf("%d",&iden);
                insert(iden);
                break;
            }
        case 2 :
            {
                display();
               break;
            }
        case 3 :
            {
                printf("Enter identity number of the record to be searched : ");
                scanf("%d",&iden);
                search(iden);
               break;
            }
        case 4 :
            {
                printf("Enter identity number of the record to be deleted : ");
                scanf("%d",&iden);
                delete(iden);
               break;
            }

        case 5 :
            {
                printf("\n");
                printf("****************************************************\n");
               exit(0);
            }
        default:
            {
                printf("Enter correct choice.\n");
            }
    }
    printf("\n");


    }
    return 0;

}
