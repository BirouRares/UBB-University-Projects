#include <stdio.h>
//Write a program to read a number of units of length (a float) and print out the area of a circle with that radius.
//Assume that the value of pi is 3.14159.
//Afterthat, change the type to double and compare the results.
int main()
{
    float r;
    printf("Enter a value for radius:\n");
    scanf("%f", &r);
    r=r*r;
    r=r*3.14159;
    printf("The area of a circle with that radius is: %.5f\n", r);

    double p;
    printf("Enter a value for radius:\n");
    scanf("%lf", &p);
    p=p*p;
    p=p*3.14159;
    printf("The area of a circle with that radius is: %lf\n", p);
    return 0;
}
