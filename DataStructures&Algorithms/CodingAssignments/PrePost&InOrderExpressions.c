#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>


typedef struct NODE
{

    struct NODE *left;
    struct NODE *right;
    char val;

}node;


node *arr[100];   //array of pointers
int location=0;


void put(node **item)
  {
    arr[location]=*item;   // will insert the new node at current location
    location+=1;
  }

node *print()
  {
    location-=1;
    return arr[location];
  }

void input(char *ptr)
  {
      int i;char temp;
      node *child;
      for(i=0;temp!='\0';i++)
      {
      temp=ptr[i];
      switch(temp)
         {
            case('-'):
            case('+'):
            case('*'):
            case('/'):

                {
                    child=(node *)malloc(sizeof(node));
                    child->val=temp;
                    child->right=print();
                    child->left=print();
                    put(&child);
                }break;
            default:  ///takes care of  in mumbers and character variables

                {
                    child=(node *)malloc(sizeof(node));
                    child->val=temp;
                    child->left=NULL;
                    child->right=NULL;
                    put(&child);
                }break;

         }
      }

  }

void pre(node *ptr)
    {
    if( ptr!=NULL)
      {
        printf("%c",ptr->val);
        pre(ptr->left);
        pre(ptr->right);
      }
}

void in(node *ptr)
    {
    if( ptr!=NULL)
      {
        in( ptr->left);
        printf("%c",ptr->val);
        in(ptr->right);
    }
}


void post(node *ptr)
   {
    if( ptr!=NULL)
      {
        post( ptr->left);
        post( ptr->right);
        printf("%c",ptr->val);
    }
}


void main()
  {
     char postexp[100];  //character array to store input postfix expression
     printf("Enter postfix expression : ");
     fgets(postexp,sizeof(postexp),stdin);

    input(postexp);

    printf("\nExpression in pre-order : ");
    pre(arr[0]);
    printf("\nExpression in in-order : ");
    in(arr[0]);
    printf("\nExpression in post-order : ");
    post(arr[0]);
}



