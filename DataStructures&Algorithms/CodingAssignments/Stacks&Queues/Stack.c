#include<stdio.h>
#include<malloc.h>
struct node
{
    int val;
    struct node *next;
    struct node *prev;
}node;

struct node *head=NULL;
struct node *tail=NULL;
struct node *temp=NULL;

void push(int num)
{
    if (head==NULL)
    {
        temp=(struct node *)malloc(sizeof(node));
        temp->val=num;
        temp->next=tail;
        temp->prev=NULL;
        head=temp;
    }
    else
    {
       temp=(struct node *)malloc(sizeof(node));
       head->prev=temp;
       temp->val=num;
       temp->next=head;
       temp->prev=NULL;
       head=temp;
    }
    //printf("Pushed into stack.\n");

}
void pop(struct node *ptr)
{
    temp=ptr;

    //printf("Popped from stack : %d\n",temp->val);
    if(temp->next==NULL)
    {
        printf("Stack is now empty.\n");
        head=tail=NULL;
        return;
    }
    head=temp->next;
    head->prev=NULL;
}

void swap(struct node *ptr)
{
    int data1,data2;
   temp = ptr;
   data1 = temp->val;
   pop(temp);
   temp=temp->next;
   data2= temp->val;
   pop(temp);
   push(data1);
   push(data2);
}
void swap2(struct node *ptr)
{
    temp=ptr;
    temp->prev=temp->next;
    temp->next->next->prev=temp;
    temp->next= temp->next->next;
    temp->prev->next=temp;
    temp->prev->prev=NULL;
    (ptr)=temp->prev;
}
void peek(struct node *ptr)
{
    temp=ptr;

    printf("Peeked from stack : %d\n",temp->val);// top-most value
}


void print(struct node *ptr)
{
    temp=ptr;
    printf("Stack: ");
    while(temp!=tail)
    {
        printf("%d->",temp->val);
        temp=temp->next;
    }
    printf("\n");
}
int main()
{

    int i=0,n,element,ch;
    printf("Enter size of stack : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter element : ");
        scanf("%d",&element);
        push(element);
    }
    printf("To pop element from stack enter 1\nTo print stack enter 2\nTo exit enter 3\nT swap enter 4\nTo peek into stack enter 5\n");
    while(1)
    {
        printf("Enter choice : ");
        scanf("%d",&ch);
        if(ch==1)
        {
            pop(head);
        }
        else if(ch==2)
        {
            print(head);
        }
        else if(ch==3)
        {
            break;
        }
        else if(ch==4)
        {
            swap(head);
            printf("swapping completed.\n");
        }
        else if(ch==5)
        {
            peek(head);
        }
        else
        {
            printf("Enter correct choice.\n");
        }

    }

    printf("\n");
    return 0;

}

