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

void tail_insert(int v)
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
        LL *temp = (LL *)malloc(sizeof(LL)); /// For 2nd and later elements
        temp->val = v;
        temp->next = NULL;
        tail->next = temp;
        tail = tail->next; /// Put new element at tail
    }
    printf("Inserted at tail\n");
}

void insert_before(int v, int n) /// Insert v before every n
{
    LL *curr, *temp; /// Two pointers, one for storing element and one for positioning
    if(head!=NULL) /// Only available while list is not empty
    {
        if(head->val==n) /// If 1st element is equal to n
        {
            temp = (LL *)malloc(sizeof(LL));
            temp->val = v;
            temp->next = head;
            head = temp; /// Head is the new element
            curr = head->next; /// Pass position after head
        }
        else curr = head; /// Set position from head

        while(curr->next!=NULL) /// Inserting operation until next is NULL
        {
            if(curr->next->val==n) /// Check value
            {
                temp = (LL *)malloc(sizeof(LL));
                temp->val = v; /// Set value to temp
                temp->next = curr->next;
                curr->next = temp;
                curr = curr->next;
            }
            curr = curr->next; /// If n is not found, Increament position
            printf("Inserted %d before %d\n",v,n);
        }
    }
}

void insert_after(int v, int n) /// Insert v after every n
{
    LL *curr, *temp; /// Two pointers, one for storing element and one for positioning
    if(head!=NULL) /// Only available while list is not empty
    {
        curr = head; /// Always start from head as inserting after

        while(curr!=NULL) /// Inserting operation until next is NULL
        {
            if(curr->val==n) /// Check value
            {
                temp = (LL *)malloc(sizeof(LL));
                temp->val = v; /// Set value to temp
                temp->next = curr->next;
                if(curr->next==NULL) tail = temp;
                curr->next = temp;
                curr = curr->next; /// Increament position
            }
            curr = curr->next; /// If n is not found, Increament position
        }
    }
}

/*void sort_linked_list()
{
    LL *i, *j, *k; /// i and j for bubble sorting, k for catching tail
    int temp; /// for swaping
    k = tail;
    for(i=head; i!=tail; i=i->next) /// Outer loop from head to tail
    {
        for(j=head; ;j=j->next) /// Inner loop from head; breaks when tail is reached
        {
            if(j->val > j->next->val) /// Comparing!!! Not 4 pieces of -> ;)
            {
                temp = j->val;
                j->val = j->next->val;
                j->next->val = temp;
            }
            if(j->next==k)
            {
                k = j;
                break; /// Breaks when tail is reached
            }
        }
    }
}
*/
void delete_all(int v) /// Deletes every v
{
    LL *temp, *curr = head;
    while(head!=NULL && head->val==v)
    {
        temp = head;
        head = head->next; /// Set next after head as new head
        free(temp); /// Delete address of head
        curr = head;
    }

    if(curr==NULL) /// Successfull deletion of all vs, go home!
    return;

    while(curr->next!=NULL) /// Deleting all next pointers
    {
        if(curr->next->val==v)
        {
            temp = curr->next;
            curr->next = curr->next->next;
            free(temp); /// Delete next after current

            if(curr->next==NULL)
            tail = curr;
        }

        else curr = curr->next; /// Move forward
    }
}

int search_linked_list(int v)
{
    LL *curr = head;
    int n = 0;
    while(curr!=NULL)
    {
        if(curr->val==v)
        return n;

        n++;
        curr = curr->next;
    }
    return -1; /// Not found :(
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
    int i;

    /// Insert 5 random value at the end
    for(i=1; i<=5; i++)
    tail_insert(rand()%99);
    tail_insert(100);

    print_linked_list();

    /// Insert 5 random value at the beg
    for(i=1; i<=5; i++)
    head_insert(rand()%99);
    head_insert(0);
    print_linked_list();
    printf("\n0 is at %d position",search_linked_list(0));
    printf("\n100 is at %d position\n",search_linked_list(100));
    delete_all(0);
    print_linked_list();

   // sort_linked_list();
   // printf("After sorting, ");
   // print_linked_list();
    return 0;
}
