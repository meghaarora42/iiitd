#include <stdio.h>

main()
{
    int array[10], *minimum, c,*maximum;

    printf("Enter 10 integers\n");

    for ( c = 0 ; c < 10 ; c++ )
        scanf("%d", &array[c]);

    minimum = array;

    for ( c = 1 ; c < 10 ; c++ )
    {
        if ( *(array+c) < *minimum )
        {
           *minimum = *(array+c);
        }
    }

    printf("Minimum element is %d.\n", *minimum);
    maximum = array;

    for ( c = 1 ; c < 10 ; c++ )
    {
        if ( *(array+c) > *maximum )
        {
           *maximum = *(array+c);
        }
    }

    printf("Maximum element is %d.\n", *maximum);
    return 0;
}
