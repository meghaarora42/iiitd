#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>

struct node
{
    int val;
    struct node *next;
    struct node *prev;
}node;

struct node *head1=NULL;
struct node *head2=NULL;
struct node *temp=NULL;

void push(struct node **ptr, int num)
{
    temp= (struct node *)malloc(sizeof(node));
    if (*ptr==NULL)
    {
        temp->val=num;
        temp->prev=NULL;
        temp->next=NULL;
        *ptr = temp;
    }
    else
    {
        temp->val=num;
        temp->next=*ptr;
        (*ptr)->prev=temp;
        temp->prev=NULL;
        *ptr=temp;

    }
}
int pop(struct node **ptr)
{
    int popped=0;
    if(*ptr==NULL)
    {
        printf("Stack is empty.\n");
        return 0;
    }
    else
    {
        temp= *ptr;
        popped = (*ptr)->val;

        (*ptr) = (*ptr)->next;
        /*(*ptr)->prev=NULL; */
        free(temp);
        return popped;
    }
}
void print(struct node **ptr)
{
    temp=*ptr;
    printf("STACK : ");
    if (temp==NULL)
    {
        printf("empty\n");
    }
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
    printf("Enter size of queue: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter element : ");
        scanf("%d",&element);
        push(&head1,element);
    }
    //printf("stack made\n");
    //print(&head1);
    //print(&head2);
    //ch=pop(&head1);
    //printf("%d",ch);
    for(i=1;i<=n;i++)
    {
        //printf("in loop\n");
        ch=pop(&head1);

        push(&head2,ch);
    }
    //print(&head1);
    //print(&head2);
    printf("Queue made using two stacks.\n");
    printf("To display enter 1\nTo pop enter 2\nTo quit enter 3\n");
    while(1)
    {
    printf("Enter choice : ");
    scanf("%d",&ch);
    switch (ch)
    {
    case 1 :
        {
            print(&head2);
            break;
        }
    case 2 :
        {
            pop(&head2);
            break;
        }
    case 3 :
        {
            exit(0);
        }
    }


    }
    return 0;
}

