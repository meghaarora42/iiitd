#include<stdio.h>
int arr[20][20],visit[20];
int result[20],j=0;
int order;

void dfs(int val)
{
    int i;
    visit[val]=1;
    printf("%d",val);
    for(i=1;i<=order;i++)
    {
        if(arr[val][i] && !visit[i])
        {
            printf("\n%d",val);
            dfs(i);
        }
    }
    j+=1;
    result[j]=val;
}
int main()
{
    int i,j;
    printf("Enter number of vertices: ");
    scanf("%d",&order);
    for(i=1;i<=order;i++)
    {
        visit[i]=0;
        for(j=1;j<=order;j++)
        {
            arr[i][j]=0;
        }
    }

    printf("\nEnter the adjacency matrix:\n");
    for(i=1;i<=order;i++)
    {
        for(j=1;j<=order;j++)
        {
            scanf("%d",&arr[i][j]);
        }
    }
    printf("\nDFS TRAVERSAL : ");
    dfs(1);
    printf("\n");
    int l;
    return 0;
}

