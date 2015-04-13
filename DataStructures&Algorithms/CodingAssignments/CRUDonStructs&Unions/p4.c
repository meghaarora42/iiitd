#include<stdio.h>
#include<string.h>

union part{
   int partnumber;
   char name[100];
   int quantity;
};
       
int main()
{
    char choice;
    union part part1,part2,part3, *ptr1 ,*ptr2,*ptr3;
    int escape=0,i,partnum,part_count;
    ptr1=&part1;
    ptr2=&part2;
    ptr3=&part3;
    (*ptr1).partnumber=1; //one record hard-coded
    strcpy((*ptr2).name,"Screw Driver");
    (*ptr3).quantity=42;
    part_count=1;
    printf("Operation Codes:\ni for insert\ns for serach\nu for update\np for print\nq for quit\n" );
    while(escape!=1)
    {
    printf("Enter operation to be performed:");
    scanf(" %c",&choice);
    switch(choice)
    {
        case 's':
             {
                 int fail=1;
                 printf("Enter Part Number\n");
                 scanf("%d",&partnum);
                 for(i=0;i<part_count;i++)
                 {

                   if((*(ptr1+i)).partnumber==partnum)
                      {
                          printf("Part name: %s\nQuantity on hand: %d\n",(*(ptr2+i)).name,(*(ptr3+i)).quantity);
                          fail=0;
                          break;
                      }
                 }
                 if(fail==1)

                      {
                          printf("Part not in inventory.\n");
                      }

              break;

              }
        case 'i':
             {
                 part_count++;
                 printf("Enter part number:\n");
                 scanf("%d",&((*(ptr1+part_count-1)).partnumber));
                 printf("Enter part name:\n");
                 fgetc(stdin);//to send empty line to buffer
                 fgets(((*(ptr2+part_count-1)).name),100,stdin);
                 printf("Enter quantity on hand:\n");
                 scanf("%d",&((*(ptr3+part_count-1)).quantity));
                 printf("Part number\tPart name\tQuantity number\n");
                 printf("%d            \t%s          \t%d\n",(*(ptr1+part_count-1)).partnumber,(*(ptr2+part_count-1)).name,(*(ptr3+part_count-1)).quantity);



              break;
             }
        case 'u':
             {
                 int fail=1,quantitychange;
                 printf("Enter part number\n");
                 scanf("%d",&partnum);
                 for(i=0;i<part_count;i++)
                 {
                     if((*(ptr1+i)).partnumber==partnum)
                       {
                         printf("Enter change quantity on hand\n");
                         scanf("%d",&quantitychange);
                         (*(ptr3+i)).quantity+=quantitychange;
                         printf("New Quantity on hand:%d\n",(*(ptr3+i)).quantity);
                         fail=0;
                         break;
                       }
                 }
                 if(fail==1)
                     {
                         printf("Part not in inventory\n");
                     }

             break;
             }
        case 'p':
             {
                 printf("Part number\tPart name\tQuantity on hand\n");
                 for(i=0;i<part_count;i++)
                 {
                    printf("%d            \t%s          \t%d\n",(*(ptr1+i)).partnumber,(*(ptr2+i)).name,(*(ptr3+i)).quantity);
                 }
             break;
             }


        case 'q':
              {
                escape=1;
                break;
              }
        default:
          {
              printf("Only i,s,q,p and u inputs allowed!\n");
          }

    }
    }
    return 0;
}

