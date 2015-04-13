#include<stdio.h>
#include<stdlib.h>

struct node{
int val;
struct node *right,*left;
}node;

struct node *root=NULL,*temp=NULL,*n=NULL;

void insert(struct node **p,int x)
{
    //struct node *trail=(struct node *)malloc(sizeof(node));
    struct node *trail=NULL;
    temp=(struct node *)malloc(sizeof(node));
    n=(struct node *)malloc(sizeof(node));
    n->val=x;
    n->right=NULL;
    n->left=NULL;
    temp=*p;
    //trail=NULL;
    while(!temp)
    {
        printf("ya");
        trail=temp;
        if(x<temp->val)
        {
            temp=temp->left;
        }
        else
        {
            temp=temp->right;
        }
    }
    if(trail==NULL)
    {
        *p=n;
    }
    else if(trail->val<x)
        trail->right=n;
    else if(trail->val>x)
        trail->left=n;
}
void insert_r(struct node **p,int x)
{
    struct node *n=(struct node *)malloc(sizeof(node));
    temp=*p;
    if(!temp)
    {
        n->val=x;
        n->left=NULL;
        n->right=NULL;
        *p=n;
    }
    else if(x < temp->val)

        insert_r(&(temp->left),x);
    else
        insert_r(&(temp->right),x);
}
void print(struct node *p)
{
   if(p->left) print(p->left);
   printf("%d\n",p->val);
   if(p->right) print(p->right);
}
int size_tree(struct node *ptr)
{
    if(ptr!=NULL)
    {
        return (size_tree(ptr->left) + 1 + size_tree(ptr->right));
    }
    else
    {
        return 0;
    }
}
int depth(struct node* ptr)           //depth in terms of number of nodes.
{
    if (ptr==NULL)
    {
        return(0);
    }
    else
    {
        int ld =depth(ptr->left);
        int rd =depth(ptr->right);
        if (ld > rd)
            return(ld+1);
        else
            return(rd+1);
    }
}

void preorder(struct node *ptr)
    {
    if( ptr!=NULL)
      {
        printf("%d\n",ptr->val);
        preorder(ptr->left);
        preorder(ptr->right);
      }
}

void inorder(struct node *ptr)
    {
    if( ptr!=NULL)
      {
        inorder( ptr->left);
        printf("%d\n",ptr->val);
        inorder(ptr->right);
    }
}


void postorder(struct node *ptr)
   {
    if( ptr!=NULL)
      {
        postorder( ptr->left);
        postorder( ptr->right);
        printf("%d\n",ptr->val);
    }
}
struct node * search(struct node *ptr , int num)
{

}


int main()
{
    int i,n,num,size,dep;
    root=NULL;
    printf("enter the number of values to be added\n");
    scanf("%d",&n);
    for(i=1;i<=n;i++)
    {
        printf("enter an element:\n");
        scanf("%d",&num);
        insert_r(&root,num);
    }
    print(root);
    size=size_tree(root);
    printf("Size of tree : %d\n",size);
    dep=depth(root);
    printf("Depth of tree : %d\n ",dep);
    //inorder(root);
    //preorder(root);
    //postorder(root);
    return 0;
}
