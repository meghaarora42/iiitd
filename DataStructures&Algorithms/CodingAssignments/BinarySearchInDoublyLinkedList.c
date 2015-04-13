#include<stdio.h>
#include<malloc.h>

struct doublylist
{
    int data;
    int index;
    struct doublylist *next;
    struct doublylist *pre;
}*head=NULL,*tail=NULL;

typedef struct doublylist n1;

n1 *cnode()
{
    n1 *temp=(n1*)malloc(sizeof(n1));
    printf("Enter the data-: ");
    scanf("%d",&temp->data);
    temp->next=NULL;
    temp->pre=NULL;
}

void end()
{
    n1 *temp=head,*temp1;
    if(head==NULL)
    {
        head=cnode();
        tail=head;
        head->index=1;
    }
    else
    {
        n1 *temp=cnode();
        int i=1;
        n1 *temp1=head;
        while(temp1->next!=NULL)
        {
            temp1=temp1->next;
            i++;
        }
        temp1->next=temp;
        temp->pre=temp1;
        temp->index=i+1;
    }
}

int len(n1 *list)
{
    n1 *temp=list;
    int c=1;
    while(temp->next!=NULL)
    {
        c++;
        temp=temp->next;
    }
    return c;
}


void display()
{
    n1* temp=head;
    while(temp!=NULL)
    {
        printf("%d->",temp->data);
        temp=temp->next;
    }
}


void binary()
{
    printf("\nEnter the value you want to search-: ");
    int val;
    scanf("%d",&val);
    int l=len(head);
    int high=l;
    int low=1,j;   //j stores index answer
    int mid;
    int found=0;
    while(low<=high && !found)
    {
        mid=(high+low)/2;
        n1 *temp=head;
        int c;
        while(temp->index!=mid)
        {
            temp=temp->next;
        }
        if(temp->data==val)
        {
            j=temp->index;
            found=1;
        }
        else if(temp->data>val)
        {
            high=(temp->index)-1;
        }
        else
        {
            low=(temp->index)+1;
        }
    }
    if(!found)
    {
        printf("\nValue not present\n");
    }
    else
    {
        printf("Value present at %d ",j);
    }
}


int main()
{
    int c;
    do
    {
        printf("\nEnter the list in the sorted manner-: \n");
        printf("Insert(1/0)?? ");
        scanf("%d",&c);
        if(c==1)
        {
            end();
        }

    }while(c!=0);
    printf("\nThe list is -: ");
    display(head);
    binary();
    return 0;
}

