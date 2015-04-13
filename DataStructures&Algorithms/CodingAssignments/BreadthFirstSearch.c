#include <stdio.h>
#define MAX 100

struct node
{
    int vertex;
    struct node *next;
};

int adj_mat[MAX][MAX]={{0}};
//struct node *adj[MAX]; //For storing Adjacency list of nodes
int vertices; //No. of Nodes in Graph
int queue[MAX],front=-1,rear=-1;  //enqueue from rear, dequeue from front

void queue_insert(int num)
{
    rear = rear+1;
    queue[rear]=num;
    if(front==-1)   //when first element enqueued
       front=0;
}

int queue_delete()
{
    int temp=queue[front];
    if(front == rear )  //last element dequeued
    {
       front=-1;
       rear=-1;
    }
    else
    {
        front = front +1;
    }
    return(temp);
}

int is_queue_empty()  //returns 1 if queue is empty
{
    if(front == -1)
    {
      return(1);
    }
    else
    {
        return(0);
    }
}
void create_graph()
{
    int i,j;
    int edges,next_vertex;  //edges to the next depth of nodes  and next_vertex is value of next node
    printf("Enter total number of nodes in the graph : ");
    scanf("%d",&vertices);
    for(i=1;i<=vertices;i++)
    {
        printf("\nEnter no. of nodes in the adjacency list of node %d:",i);
        scanf("%d",&edges);
        if(edges!=0)
        {
            for(j=1;j<=edges;j++)
            {
                printf("\nEnter node : ");
                scanf("%d",&next_vertex);
                adj_mat[i][next_vertex]=1;
            }
        }
    }
}


void BFS_traversal()
{
    int dequeued,i,j;
    int start_node,status[MAX];//status not visited =1,visiting=2(in queue),visited=3; //status of node.

    printf("Enter starting node : ");
    scanf("%d",&start_node);

    for(i=1;i<=vertices;i++)   //all nodes not visited
    {
        status[i]=1;
    }
    queue_insert(start_node); //First node in queue.
    status[start_node]=2;
    printf("BFS Traversal :        ");
    // to account for nodes with initial indegree 0 other than starting node
    for(i=1;i<=vertices;i++)
    {
        int sum=0;
        if(i != start_node)
        {
           for(j=1;j<=vertices;j++)
            {
                sum += (adj_mat[j][i]);
            }
        }
        if(sum == 0 && i!=start_node )
        {
            queue_insert(i);
            status[i]=2;
        }
    }
    while(is_queue_empty()!=1)
    {
        dequeued = queue_delete(); //remove front node of queue.
        status[dequeued]=3;
        printf("%d   ",dequeued);
        for(j=1;j<=vertices;j++)
        {
            if (adj_mat[dequeued][j]==1 && status[j] != 2 && status[j] != 3)
            {
                queue_insert(j);
                status[j]=2;    //in queue to be visited
            }
        }
    }
}

int main()
{
    printf("Breadth First Search\n");
    printf("Creating graph:\n");
    create_graph();
    printf("\n");
    printf("Adjacency Matrix for graph:\n");
    printf("\n");
    int i,j;
    for(i = 1;i <= vertices;i++)
    {
        printf("\t");
        for(j = 1;j <= vertices;j++)
        {
            {
                printf("%d ",adj_mat[i][j]);
            }
        }
          printf("\n");
    }
    printf("\n");
    BFS_traversal();
    return 0;
}
