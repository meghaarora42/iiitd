#include<stdio.h>
#include<stdlib.h>
typedef struct linked_list {
    int val;
    struct linked_list *next;
    struct linked_list *prev;
} LL;

LL *head, *tail;

void head_insert(int v)
{
    if(head==NULL)
    {
       head=(LL *)(malloc(sizeof(LL)));
       head->val=v;
       head->next=NULL;
       tail=head;
    }
    else
    {
        LL *temp = (LL *)(malloc(sizeof(LL)));
        temp->val=v;
        temp->next=head->next;
        temp->prev=head;
        head->next->prev=temp;
        head->next=temp;

    }
    printf("Inserted at head\n");
}
void print_linked_list()
{
    LL *curr = head;
    printf("Current linked list:\n");
    while(curr!=NULL) /// Loop :D
    {
        printf("%d ", curr->val);
        curr = curr->next; /// Move forward
    }
    printf("\n\n");

}
int main()
{
    int a,b,c,d,e;
    printf("Enter 5 values");
    scanf("%d",&a);
    head_insert(a);
    scanf("%d",&b);
    head_insert(b);
    scanf("%d",&c);
    head_insert(c);
    scanf("%d",&d);
    head_insert(d);
    scanf("%d",&e);
    head_insert(e);
    print_linked_list();
    return 0;

}
