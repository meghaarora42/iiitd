
#include<stdio.h>
#include<stdlib.h>
void heap_build(int arr[],int size)
{
    int i,j;
    int  child,parent;
    for(j=2;j<=size;j++)  ///Begins after the root node,arr[1]=root
    {
        child=j;
        parent =(int)child/2; /// arr[2] and arr[3] are children to arr[1] and so on.
        int temp;
        while(child > 1 && arr[child] > arr[parent])  ///building max-heap
        {
            /// swapping the elements
            temp=arr[child];
            arr[child]= arr[parent];
            arr[parent]=temp;
            ///repating till root node is reached
            child=parent;
            parent=(int)child/2;
            if(parent < 1) /// when child=1, root=0, for last iteration so make root =1 again
            {
                parent=1;
            }
        }
    }
    printf("\nHeap: ");
    for(i=1;i<=size;i++)
    {
        printf("   %d",arr[i]);
    }
}


void heap_sort(int arr[],int size)
{
    int temp,parent,child;
    int i,position;
    for(position=size;position>1;position--) ///for all nodes except root node
    {
        temp=arr[position];
        arr[position]=arr[1];   ///storing the max value at its correct position
        parent=1;
        if (position > 3 && arr[3] > arr[2])  ///obtaining the greater child of the root node
        {
            child=3;
        }
        else
        {
            child = 2;
        }
        while (child < position && arr[child]>=temp)  ///finding correct position for temp
        {
            arr[parent]=arr[child];           ///moving the greter value up
            parent=child;                     ///going one step down
            child=child*2;
            if(child+1 <= position-1 && arr[child+1] > arr[child])   ///child is the greter of the two children
            {
                    child = child + 1;
            }
        }
        arr[parent]=temp;             ///putting back temp at the correct position in heap
    }
    printf("\nHeap Sort Complete:   ");
    for(i=1;i<=size;i++)
    {
       printf("%d   ",arr[i]);
    }
}



int main(void)
{
   int array[100];
   int size,i;
   printf("Heap Sort\n\n");
   printf("*****************\n\n");
   printf("Enter the no. of elements: ");
   scanf(" %d",&size);
   printf("\nEnter the elements: ");
   for(i=1;i<=size;i++)
   {
       scanf("%d",&array[i]);
   }

   heap_build(array,size);
   printf("\n");
   heap_sort(array,size);
   printf("\n");
   printf("\n\n*****************\n\n");
   return 0;
}

