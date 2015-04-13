#include<stdio.h>

int fib(int n)
{
    if(n==0)
    {
        return 0;
    }
    else if(n==1)
    {
        return 1;
    }
    else
    {
        return fib(n-1)+fib(n-2);
    }
}

int is_prime(int n)
{
    int flag=0,j;
    for(j=2;j<n;j++)
    {
        if(n%j == 0)
        {
            flag=1;
        }
    }
    if(flag==1)
    {
        return 0; //not prime
    }
    else
    {
        return 1;  //prime
    }
}

int main()
{
    int n,count,i=3,num;
    printf("Enter n to get nth fibonacci prime: ");
    scanf("%d",&n);
    count=n;
    while(count!=0)
    {
        num=fib(i);
        if(is_prime(num)==0)
        {
            i++;
            continue;
        }
        if(is_prime(num)==1)    //prime found
        {
            count--;
        }
        i++;
    }
    printf("%dth fibonacci prime is : %d ",n,num);
    return 0;
}


