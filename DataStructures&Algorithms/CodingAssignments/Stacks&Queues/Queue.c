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
        temp->next=NULL;
        temp->prev=NULL;
        tail=temp;
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
    printf("Pushed into queue.\n");

}
void pop(struct node *ptr)
{
    temp=ptr;

    printf("Popped from queue : %d\n",temp->val);
    if(temp->prev==NULL)
    {
        printf("Queue is now empty.\n");
        head=tail=NULL;
        return;
    }
    tail=temp->prev;
    tail->next=NULL;

}
void print(struct node *ptr)
{
    temp=ptr;
    printf("Queue: ");
    while(temp!=NULL)
    {
        printf("%d->",temp->val);
        temp=temp->next;
    }
    printf("\n");
}
int main()
{

    int i=0,n,element,ch;
    printf("Enter size of queue : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter element : ");
        scanf("%d",&element);
        push(element);
    }
    printf("To pop element from queue enter 1\nTo print queue enter 2\nTo exit enter 3\n");
    while(1)
    {
        printf("Enter choice : ");
        scanf("%d",&ch);
        if(ch==1)
        {
            pop(tail);
        }
        else if(ch==2)
        {
            print(head);
        }
        else if(ch==3)
        {
            break;
        }
        else
        {
            printf("Enter correct choice.\n");
        }

    }

    printf("\n");
    return 0;

}

