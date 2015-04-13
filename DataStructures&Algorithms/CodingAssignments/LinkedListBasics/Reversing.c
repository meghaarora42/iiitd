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

void insertnum(int num)
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

}

void print(struct node *ptr)
{
    temp=ptr;
    printf("List: ");
    while(temp!=tail)
    {
        printf("%d->",temp->val);
        temp=temp->next;
    }
}

void swapptr(struct node **ptr1, struct node **ptr2)
{
    struct node *temp;
    temp= *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}

struct node *reverselist(struct node *p)
{
    if (p==NULL)   //end of list
    {
        return p;
    }
    swapptr(&(p->next), &(p->prev));
    if (p->prev==NULL)   //beginning of list
    {
        return p;
    }
    return reverselist(p->prev);
}

int main()
{

    int i=0,n,element;
    printf("Enter size of list : ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("Enter element : ");
        scanf("%d",&element);
        insertnum(element);
    }
    print(head);
    printf("\n");
    struct node *answer=reverselist(head);
    printf("Reversing complete\n");
    print(answer);
    return 0;

}
