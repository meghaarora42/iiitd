#include <stdio.h>
#include <stdlib.h>

typedef struct linked_list {
    int val;
    struct linked_list *next;
} LL;

LL *head, *tail; /// take two pointer to define start and end of list

void head_insert(int v)
{
    if(head==NULL) /// Only for 1st element
    {
        head = (LL *)malloc(sizeof(LL));
        head->val = v;
        head->next = NULL;
        tail = head; /// For only 1 element, head = tail
    }
    else
    {
        LL *temp = (LL *)malloc(sizeof(LL));
        temp->val = v;
        temp->next = head;
        head = temp; /// Put new element at head
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




