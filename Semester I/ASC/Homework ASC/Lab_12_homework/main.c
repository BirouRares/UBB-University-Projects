#include <stdio.h>

int increment(int a);// the function declared in modul.asm

int main()
{
    int i=32;//start from 32
    while(i<=126)//
    {
        printf("The character with this ASCII code is --> %c\n",i);//print the character for that ASCII code
        printf("The number in base 8 is --> %o\n\n",i);//print the number in base 8
        i=increment(i); //increase the i with 1 calling the asm function
    }
    return 0;
}
