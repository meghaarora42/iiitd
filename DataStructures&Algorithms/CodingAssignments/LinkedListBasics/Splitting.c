#include <stdio.h>
#include <malloc.h>

struct node
{
    int data;
    struct node *next;
}*tail,*first,*second,*firstptr,*secondptr;

create(int num)
{
    struct node *temp;
    temp= malloc(sizeof(struct node));
    temp->data = num;

    if(tail == NULL)

    {
        tail = temp;
        temp->next = tail;
    }
    else
    {
        temp->next = tail->next;
        tail->next = temp;
        tail = temp;
    }
}
print(struct node *ptr)
{
    struct node *temp;
    if(ptr == NULL)
    {
        printf("List is empty\n");
        return;
    }
    temp = ptr->next;
    printf("Circular list is :\n");
    while(temp != ptr)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("%d\n",ptr->data);
}/*End of display()*/

void ListSplit(struct node *linklist, struct node *first, struct node *second)
{
    if (linklist == 0)
    {
        first = 0;
        second = 0;
        printf("empty list can't be split");
        return;
    }

    first = linklist;
    second = linklist->next;
    firstptr = first;    //firstptr anchors to the first element as first moves along the first list
    secondptr = second;    ////secondptr anchors to the first element as second moves along the second list
    linklist = linklist->next->next;

    while (linklist != firstptr)  // not first as first has moved ahead
    {
        first = first->next = linklist;
        second = second->next = linklist->next;
        linklist = linklist->next->next;
    }
    linklist = 0;
    first->next = firstptr;
    second->next = secondptr;

}
int main()
{
    int n,element,i;
    tail=NULL;
    printf("Enter even number for number of nodes : ");
    scanf("%d",&n);
    if(n%2 != 0)
    {
        printf("Only even number can be entered.");
        exit(1);
    }
    for(i=0; i < n;i++)
    {
        printf("Enter the element : ");
        scanf("%d",&element);
        create(element);
    }
    print(tail);
    ListSplit(tail,first,second);
    printf("Splitting completed.\n");
    print(firstptr);
    print(secondptr);
    return 0;

}
