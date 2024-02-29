#include <stdio.h>
// Read two integers and compute their sum, average and sum of the squares of the numbers.
int main()
{
    int x,y;
    printf("Type the numbers:\n");
    scanf("%d", &x);
    scanf("%d", &y);

    int sum=0;
    sum=x+y;
    printf("The sum of the numbers is: ");
    printf("%d",sum);
    printf("\n");

    float avg=0;
    avg=(float)(sum)/2;
    printf("The average of the numbers is: ");
    printf("%.2f",avg);
    printf("\n");

    int sum_of_the_squares=0;
    x=x*x;
    y=y*y;
    sum_of_the_squares=x+y;
    printf("The sum of the squares of the numbers is: ");
    printf("%d",sum_of_the_squares);
    printf("\n");

    return 0;
}
