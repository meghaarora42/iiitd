#include<stdio.h>
#include<math.h>
#include<string.h>
void octal_hex(int n,char hex[]);
int hex_octal(char hex[]);
int main()
{
    char hex[20];int c;
    int n;
    printf("Press 1 to convert oct to hex:\n");
    printf("Press 2 to hex number to oct:\n");
    scanf("%d",&c);
    if(c==1)
    {
        printf("Enter octal number: ");
        scanf("%d",&n);
        octal_hex(n,hex);
        printf("Hexadecimal number:%s", hex);
    }
    if(c==2)
    {
        printf("Enter hexadecimal number:");
        scanf("%s",&hex);
        printf("Octal num: %d",hex_octal(hex));
    }
    return 0;
}
void octal_hex(int n,char hex[])
{
    int i=0,decimal=0, rem;
    while (n!=0)
    {
        rem = n%10;
        n/=10;
        decimal += rem*pow(8,i);
        ++i;
    }
/* At this point, decimal contains the decimal value of given octal number. */
    i=0;
    while (decimal!=0)
    {
        rem=decimal%16;
        switch(rem)
        {
            case 10:
              hex[i]='A';
              break;
            case 11:
              hex[i]='B';
              break;
            case 12:
              hex[i]='C';
              break;
            case 13:
              hex[i]='D';
              break;
            case 14:
              hex[i]='E';
              break;
            case 15:
              hex[i]='F';
              break;
            default:
              hex[i]= rem+'0';  //to typecast it to character, alternate (char)rem
              break;
        }
        ++i;
        decimal/=16;
    }
    hex[i]='\0';
    strrev(hex);       /* Function to reverse string. */
}

int hex_octal(char hex[])   /* Function to convert hexadecimal to octal. */
{
    int i, length, decimal=0, octal=0;
    for(length=0; hex[length]!='\0'; ++length);
    for(i=0; hex[i]!='\0'; ++i, --length)
    {
        if(hex[i]>='0' && hex[i]<='9')
            decimal+=(hex[i]-'0')*pow(16,length-1);
        if(hex[i]>='A' && hex[i]<='F')
            decimal+=(hex[i]-55)*pow(16,length-1);
        if(hex[i]>='a' && hex[i]<='f') //compares ASCII values
            decimal+=(hex[i]-87)*pow(16,length-1);
    }
/* At this point decimal contains the decimal value of given hexadecimal number. */
    i=1;
    while (decimal!=0)
    {
        octal+=(decimal%8)*i;
        decimal/=8;
        i*=10;
    }
    return octal;
}

