#include<stdio.h>
#include<malloc.h>
#define SIZE 100

typedef struct linked_list
{
    int val;
    struct linked_list *next;
} LL;

int n;
int indeg[SIZE]={0};   //array storing indegrees
int adj_mat[SIZE][SIZE]={{0}};

LL *head, *tail;

void tail_insert(int v)
{
    if(head==NULL) /// Only for 1st element
    {
        head = (LL *)malloc(sizeof(LL));
        head->val = v;
        head->next = NULL;
        tail = head;
    }
    else
    {
        LL *temp = (LL *)malloc(sizeof(LL));
        temp->val = v;
        temp->next = NULL;
        tail->next = temp;
        tail = tail->next;
    }
    //printf("Inserted at tail\n");
}
void print_linked_list()
{
    LL *curr = head;
    //printf("Linked list:\n");
    while(curr!=NULL)
    {
        printf("%d->", curr->val);
        curr = curr->next;
    }
    printf("\n\n");
}
void graph_build(int num_vertices)
{
    int i=0,j=0,max_edges;
    int start,end;
    max_edges = num_vertices * (num_vertices - 1);
    /*for(i=1;i<=num_vertices;i++)

    {
        for(j=1;j<=num_vertices;j++)
        {
            adj_mat[i][j]=0
        }
    }*/
    for(i = 1;i <= max_edges;i++)
    {
        printf("\nEnter edge %d (Enter from '0' to '0' to quit): from ",i);
        scanf("%d",&start);
        printf(" to ");
        scanf("%d",&end);
        if((start == 0) && (end == 0))
        {
            return;
        }
        else
        {
            adj_mat[start][end] = 1;
        }
    }
    return;
}
void show_graph()
{
    int i,j;
    for(i = 1;i <= n;i++)
    {
        printf("\t%d->",i);
        for(j = 1;j <= n;j++)
        {
            if(adj_mat[i][j]==1)
            {
                printf("%d->",j);
            }
        }
          printf("\n");
    }
}
int indegree(int vertex)
{
    int i,in_deg = 0;
    for(i = 1;i <= n;i++)
    {
       if(adj_mat[i][vertex] == 1)
       {
            in_deg++;
       }
    }
   return in_deg;
}
int check_cyclic()
{
    int check=1,i=0;           ///check for cyclic 1:cyclic,0:acyclic
    for(i=1;i<=n;i++)
    {
        if(indeg[i]== 0)
        {
            check = 0;
            break;
        }
    }
    return check;
}

int main()
{
    int i = 0,j = 0,k;
    printf("\nEnter number of vertices: ");
    scanf("%d",&n);
    graph_build(n);
    printf("Adjacency Matrix for graph:\n");
    printf("\n");
    for(i = 1;i <= n;i++)
    {
        printf("\t");
        for(j = 1;j <= n;j++)
        {
            {
                printf("%d ",adj_mat[i][j]);
            }
        }
          printf("\n");
    }
    printf("\n");
    printf("Adjacency List for graph:\n");
    printf("\n");
    show_graph();
    for(i=1;i<=n;i++)
    {
            indeg[i]=indegree(i);
    }

    if((check_cyclic())==1)
    {
        printf("\nTopological sort not applicable on cyclic graphs.\n");
        exit(0);
    }
    int flag=1;
    while(flag==1)
    {
        for(i=1;i<=n;i++)    //recomput indegrees after each loop
        {
            if(indeg[i]!=-1)  //only if it is not already removed
            {
                indeg[i]=indegree(i);
            }
        }
        for(i=1;i<=n;i++)
        {
            if(indeg[i]==0)
            {
                tail_insert(i);    //put in linked list
                for(j=1;j<=n;j++)   // affect on adjacent vertices
                {
                    adj_mat[i][j]=0;
                }
                indeg[i]=-1;   //will no longer be computed on
            }
        }
        flag=0;
        for(i=1;i<=n;i++)
        {
            if(indeg[i]!= -1)
            {
                flag=1;
            }
        }
    }
    printf("\nTopologically sorted nodes:\n");
    printf("\n");
    print_linked_list();
    printf("\n");
    return 0;
}
