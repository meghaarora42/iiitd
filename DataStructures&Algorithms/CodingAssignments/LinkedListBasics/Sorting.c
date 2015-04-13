#include <stdio.h>
#include <malloc.h>

typedef struct node
{
    int val;
    struct node *next;
} linklist;

linklist *head, *tail;

void head_insert(int v)
{
    if(head==NULL)
    {
        head = (linklist *)malloc(sizeof(linklist));
        tail = (linklist *)malloc(sizeof(linklist));
        head->val = v;
        head->next = NULL;
        tail = head;
    }
    else
    {
        linklist *temp = (linklist *)malloc(sizeof(linklist));
        temp->val = v;
        temp->next = head;
        head = temp;
    }
}
void print()
{
    linklist *temp = head;
    printf("Linked List:\n");
    while(temp!=NULL)
    {
        printf("%d ", temp->val);
        temp = temp->next;
    }
}
void sort_list()
{
    linklist *i, *j, *k,*temp;
    temp=head;
    int var;
    k = tail;
    for(i=head; i!=tail; i=i->next)
    {
        for(j=head;;j=j->next) //buublesort
        {
            if(j->val > j->next->val)
            {
                var = j->val;
                j->val = j->next->val;
                j->next->val = var;
            }
            if(j->next==k)
            {
                k = j;
                break;
            }
        }
    }
}
int main()
{
    int i,element,n;
    printf("Enter number of nodes : ");
    scanf("%d",&n);
    for(i=0; i < n;i++)
            {
                printf("Enter the element : ");
                scanf("%d",&element);
                head_insert(element);
            }
    print();
    sort_list();
    printf("\nSorting completed\n");
    print();
    return 0;
}

