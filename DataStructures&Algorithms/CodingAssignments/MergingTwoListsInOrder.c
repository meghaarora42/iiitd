#include<stdio.h>
#include<malloc.h>

struct doublylist
{
    int data;
    struct doublylist *next;
    struct doublylist *pre;
}*head1=NULL,*head2=NULL,*head3=NULL;

typedef struct doublylist n1;

n1 *cnode()
{
    n1 *temp=(n1*)malloc(sizeof(n1));
    printf("Enter the data-: ");
    scanf("%d",&temp->data);
    temp->next=NULL;
    temp->pre=NULL;
    return temp;
}

void end(n1 **list)
{
    n1 *temp=(*list),*temp1;
    if((*list)==NULL)
    {
        (*list)=cnode();
    }
    else
    {
        n1 *temp=cnode();
        n1 *temp1=(*list);
        while(temp1->next!=NULL)
        {
            temp1=temp1->next;
        }
        temp1->next=temp;
        temp->pre=temp1;
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


void display(n1 *list)
{
    n1* temp=list;
    while(temp!=NULL)
    {
        printf("%d->",temp->data);
        temp=temp->next;
    }
}

void merge(n1 *list1,n1 *list2)
{
    n1 *temp1=list1,*temp2=list2;
    while(temp1!=NULL && temp2!=NULL)
  {
     // printf("kkk");

   if(temp1->data < temp2->data)
    {
        //printf("lll");
        if(head3==NULL)                       //smaller value inserted first in empty head3
        {
            head3=(n1*)malloc(sizeof(n1));
            head3->data=temp1->data;
            head3->next=NULL;
            head3->pre=NULL;
            temp1=temp1->next;
        }
        else                                  //smaller value inserted in filled head3
        {
            n1 *temp3=head3;
       //     printf("mm");
            while(temp3->next!=NULL)
            {
                temp3=temp3->next;
            }
         //   printf("jj ");
            n1 *temp8=(n1*)malloc(sizeof(n1));
          //  printf("jj ");
            temp8->data=temp1->data;
            //printf("jj ");
            temp3->next=temp8;
           // printf("jj ");
            temp3->next->pre=temp3;
           // printf("jj ");
            temp8->next=NULL;
           // printf("jj \n");
            temp1=temp1->next;
        }
    }

        else if(temp2->data<temp1->data)
        {
            if(head3==NULL)
            {
                head3=(n1*)malloc(sizeof(n1));
                head3->data=temp2->data;
                head3->next=NULL;
                head3->pre=NULL;
                temp2=temp2->next;
            }
            else
            {
                n1 *temp4=head3;
                while(temp4->next!=NULL)
                {
                    temp4=temp4->next;
                }
                n1 *temp8=(n1*)malloc(sizeof(n1));
                temp8->data=temp2->data;
                temp4->next=temp8;
                temp4->next->pre=temp4;
                temp8->next=NULL;
                temp2=temp2->next;
            }
        }
        else                    // same value in temp1 and temp2 only once addded in head3
        {
            if(head3==NULL)
            {
                head3=(n1*)malloc(sizeof(n1));
                head3=temp2;
                head3->next=NULL;
                head3->pre=NULL;
                temp2=temp2->next;
                temp1=temp1->next;
            }
            else
            {
                n1 *temp4=head3;
                while(temp4->next!=NULL)
                {
                    temp4=temp4->next;
                }
                n1 *temp8=(n1*)malloc(sizeof(n1));
                temp8->data=temp2->data;
                temp4->next=temp8;
                temp4->next->pre=temp4;
                temp8->next=NULL;
                temp2=temp2->next;
                temp1=temp1->next;

            }
        }

  }
        while(temp1!=NULL)   //temp1 mein kuch bacha hai toh daal do
        {
            n1 *temp4=head3;
            while(temp4->next!=NULL)
            {
                temp4=temp4->next;
            }
            n1 *temp8=(n1*)malloc(sizeof(n1));
            temp8->data=temp1->data;
            temp4->next=temp8;
            temp4->next->pre=temp4;
            temp8->next=NULL;
            temp1=temp1->next;
        }

        while(temp2!=NULL)             //temp2 mein kuch bacha hai toh daal do
        {
            n1 *temp4=head3;
            while(temp4->next!=NULL)
            {
                temp4=temp4->next;
            }
            n1 *temp8=(n1*)malloc(sizeof(n1));
            temp8->data=temp2->data;
            temp4->next=temp8;
            temp4->next->pre=temp4;
            temp8->next=NULL;
            temp2=temp2->next;
        }
}

    int main()
    {
        int c;
        printf("Enter first list(sorted)-:\n");
        do
        {
            printf("\nInsert?(1/0)-: ");
            scanf("%d",&c);
            if(c==1)
            {
                end(&head1);
            }

        }
        while(c!=0);
        printf("Enter second list(sorted)-:\n");
        do
        {
            printf("\nInsert?(1/0)-: ");
            scanf("%d",&c);
            if(c==1)
            {
                end(&head2);
            }

        }
        while(c!=0);

        printf("First list is-: ");
        display(head1);
        printf("\n");
        printf("Second list is-: ");
        display(head2);
        printf("\n");
        printf("Merged list is-: ");
        merge(head1,head2);
        display(head3);
        return 0;
    }

