#include<stdio.h>
#include<stdlib.h>

struct node
{
            int val;
            struct node *next;
            struct node *prev;
};
struct node *src=NULL,*dest=NULL,*spare=NULL;


void print(struct node **ptr)
{
         struct node *temp;
         temp=*ptr;
         if(temp==NULL)
         {
                          // printf("Stack is empty.\n");
         }
         while(temp!=NULL)
         {
                  printf("%d->",temp->val);
                  temp=temp->next;
         }
         printf("\n");
}

void push(struct node **ptr,int num)
{
         struct node *temp=(struct node *)(malloc(sizeof(struct node)));
         temp->val=num;
         temp->next=NULL;
         temp->prev=NULL;
         if(*ptr==NULL)
         {
                    temp->next=NULL;
                    *ptr=temp;
         }
         else
         {
                temp->next=*ptr;
                (*ptr)->prev=temp;
                *ptr=temp;
         }
}

int pop(struct node **ptr)
{
     struct node *temp;
     temp=*ptr;
     int popped;
     if (*ptr==NULL)
     {
         //printf("Stack is empty\n");
     }
     else
     {
            *ptr=temp->next;
            popped=temp->val;
            //printf("Popped:%d",temp->val);
            free(temp);
            return popped;
     }
}
void shift(struct node **movefrom,struct node **moveto)
{
    int num;
    num=pop(movefrom);
    push(moveto,num);
}

void tower(int disk,struct node **source,struct node **destination,struct node **sparestack)
{
    if(disk==1)
    {
        shift(source,destination); //moveing from source to destination
        printf("Source:");
        print(source);
        printf("Destination:");
        print(destination);
        printf("Spare:");
        print(sparestack);
        printf("\n");

    }
    else
    {
        tower((disk-1),source,sparestack,destination);
        shift(source,destination); //move from source to destination
        printf("Source:");
        print(source);
        printf("Destination:");
        print(destination);
        printf("Spare:");
        print(sparestack);
        printf("\n");
        tower((disk-1),sparestack,destination,source);
    }

}

int main()
{
    int total,i=0;
    printf("Enter number of discs in the tower of hanoi:");
    scanf(" %d",&total);
    for((i=total-1);i>=0;i--)
    {
        //printf("enterind %d",i);
        push(&src,i);
    }


    print(&src);
    print(&dest);
    print(&spare);
    //pop(&src);
    //print(&src);


   tower(total,&src,&spare,&dest);
    return 0;
}

