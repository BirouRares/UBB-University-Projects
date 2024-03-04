/*a. Generate all the prime numbers smaller than a given natural number n.
b. Given a vector of numbers, find the longest increasing contiguous subsequence, such the sum of that any 2 consecutive elements is a prime number.*/
#include <stdio.h>
int is_n_prime(int n)//This function test if the input number is prime
{
    int d = 2, prime = 1;
    if (n == 1 || n == 0)
        prime = 0;
    while (d * d <= n && prime == 1)
    {
        if (n % d == 0)
            prime = 0;
        d++;
    }
    if (n==4)
    	prime=0;
    return prime;//if the number is prime, the function returns 1, otherwise 0
}

void generate_prime_numbers(int n)//This function prints all prime numbers until the value n
{
    int i;
    for (i = 1; i <= n; i++)
    {
        if (is_n_prime(i) == 1)
            printf("%d ", i);
    }
    printf("\n");
}

void longest_increasing_subsequence_with_prime_sums(int a[], int n) {//This function prints the longest increasing subsequence with prime sums of 2 consecutive elements
    int start=0,end=0,max_len=0;

    for (int i = 0; i < n; i++) {
        int j = i + 1;//here a new sequence is started
        while (j<n && a[j]>a[j - 1] && is_n_prime(a[j] + a[j - 1])) {      //While the next element is bigger than the previous one and the sum of the 2 consecutive elements is prime, the sequence is extended
			j++;//take the next element
		}
        if (j - i > max_len) {//if the length of the current sequence is bigger than the previous one, the new sequence is saved
			max_len=j-i;//update the length of the longest sequence
			start=i;//update the start of the longest sequence
			end=j-1;//update the end of the longest sequence
		}
    }
    printf("The lenght of the longest increasing contiguous subsequence with prime sums: %d \n", max_len);
    printf("Longest increasing contiguous subsequence with prime sums:\n");
    for (int i = start; i <= end; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");//print the length of the longest sequence and the sequence itself
}

void read(int n, int v[])//This function reads the array
{
    int i;
    printf("The elements of the array are: \n");
    for (i = 0; i < n; i++)
        scanf("%d", &v[i]);
}

int main()
{
    int opt, ok, i, m,nr=0;
    int n=0, v[1000];//all the variables are declared locally
    ok = 1;
    while (ok == 1)//while do not have an exit command
    {
        if (nr == 0)
            nr++;
        else
            printf("\n");
        printf("Menu:\n");//Here we print the menu, so the user can choose what he wants to do
        printf("1.Read vector and n \n");
        printf("2.Problem a\n");
        printf("3.Problem b\n");
        printf("4.Exit\n");
        printf("Your option: ");
        scanf("%d", &opt);//read the user's option

        if (opt == 4)//Exit command
        {
            printf("\nTake care!\n");
            ok = 0;
        }
        if (opt == 1)//array input
        {   
            printf("The value for n: ");
            scanf("%d", &n);
            read(n,v);
            printf("\n%d\n", n);
            for(i=0;i<n;i++)
                printf("%d ", v[i]);
        }
        if (opt == 2)//prime numbers generation
        {
            printf("The value for n is: ");
            scanf("%d", &m);
            generate_prime_numbers(m);
        }
        if (opt == 3)//longest increasing subsequence with prime sums
        {
            if (n != 0)
                longest_increasing_subsequence_with_prime_sums(v, n);
            else
                printf("Please input the array first!\n");
        }
    }
    return 0;
}
