#include<stdio.h>
#include <time.h>

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

int fib(int n)
{
    if(n == 1)
    {
        return 0;
    }
    else if(n == 2)
    {
        return 1;
    }
    else
    {
        //printf("%d",fib(n-1) + fib(n-2));
        return (fib(n-1) + fib(n-2));
    }
}

int main()
{

    int n,num,i;
    long unsigned int time;
    printf("Enter n to obtain fibonacci series upto n : ");
    scanf("%d",&n);
    printf("Fibonacci Series : ");
    //startTimer();
    for(i=1;i<=n;++i)
    {
            num=fib(i);
            printf("%d, ",num);
    }
    //time= stopTimer();
    //printf("%ld",time);

    return 0;
}
