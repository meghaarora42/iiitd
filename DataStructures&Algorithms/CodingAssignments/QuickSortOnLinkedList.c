#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include <time.h>
#define qsort(n) qsort_segment(n, NULL)


//Global Variables
unsigned int timer;
unsigned int timer2;
void startTimer()
{
    timer = clock();
}
int stopTimer()
{
    timer2 = clock();
    timer = timer2 - timer;
    return timer;
}

struct node
{
    int data;
    struct node *prev;
    struct node *next;
}LL;

struct node *listhead()
{
    struct node *ptr=(struct node *)malloc(sizeof(LL));
    ptr->prev=NULL;
    ptr->next=NULL;
    return ptr;
}
struct node *new_node(int val)
{
    struct node *temp=(struct node *)malloc(sizeof(LL));
    temp->data=val;
    return temp;
}
void insert_node(struct node *ptr,struct node *newnode)  //inserts after ptr
{
    newnode->prev=ptr;
    newnode->next=ptr->next;
    if(ptr->next)
    {
        ptr->next->prev=newnode;
    }
    ptr->next=newnode;
}
void remove_node(struct node *ptr)
{
    if(ptr->prev)            //ptr cannot be head
    {
        ptr->prev->next=ptr->next;
        if(ptr->next)         // incase removing last element
        {
            ptr->next->prev=ptr->prev;
        }
    }
}

void qsort_segment(struct node *beg,struct node *end)
{
    if (beg==end || beg->next == end)
    {
        return;
    }
    struct node *piv=beg->next;   //first element is the pivot
    struct node *i, *temp, *temp2 = piv;
    struct node *x = end ? end->next : NULL;
    for(i=piv->next;i!=x;i=temp)
    {
        temp=i->next;
        remove_node(i);
        if (i->data < piv->data)
        {
            insert_node(beg,i);
        }
        else
        {
            insert_node(piv, temp2 == piv ? (temp2 = i) : i);
        }
    }
    void qsort_step_display(struct node *p);    //function made below
    qsort_step_display(piv);
    qsort_segment(piv, temp2);   //sorting new segments on right
    qsort_segment(beg, piv->prev);   //sorting new segments on left
}
void display(struct node *ptr)
{
    while (ptr)
    {
        printf("%d ", ptr->data);
        ptr=ptr->next;
    }
}
void make_list(struct node *ptr,int n)      //being made randomly
{
    srand(time(NULL));//prevent getting a consecutive series of random numbers that are exactly the same
    while (n--)
    {
        insert_node(ptr,new_node(rand() % 100));
    }
}
struct node *head;
int main()
{
    int size;
    long unsigned int time;
    head = listhead();
    printf("Enter size of list : ");
    scanf("%d",&size);
    make_list(head,size);

    printf("List randomly generated: ");
    display(head->next);
    printf("\n\n");
    //startTimer();
    qsort(head);
    printf("\n");
    //time= stopTimer();
    //printf("%ld\n",time);
    printf("List sorted: ");
    display(head->next);
    printf("\n");
    return 0;
}
void qsort_step_display(struct node *ptr)
{
    struct node *temp = head;
    while ((temp = temp->next))
    {
            printf("  %d ", temp->data);
    }
    printf("\n");
}











