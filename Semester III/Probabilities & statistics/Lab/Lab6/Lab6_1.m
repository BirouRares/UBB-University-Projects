%1.a


alfa=input("Input the significat level(0-1): ");
X= [7,7,4,5,9,9,4,12,8,1,8,7,3,13,2,1,17,7,12,5,6,2,1,13,14,10,2,4,9,11,3,5,12,6,10,7];

n=length(X);

%The null hypot. H0: u=0.5(Goes toghether with u>8.5,standard is met)
%The alternative hypot H1: u<0.5(Standart is not met)
%This is a left tail test for u

printf("\nSolving 1a, left tail test for the mean, when sigma is known\n\n");

sigma=5;
m0=8.5;

[h,p,ci,zval]=ztest(X,m0,sigma,"alpha",alfa,"tail","left");

z=norminv(alfa,0,1);

RR=[-inf z];

printf("The value of h is %d\n", h);

if (h==1)
  printf("\nThe null hypot is rejected\n");
  printf("The data sugest that the standard is not met\n\n");

else
  printf("The null hypot is not rejected\n");
  printf("\nThe data sugets that the standard is met\n\n");
endif


printf("The rejection region is: (%4.4f, %4.4f)\n",RR);
printf("The observered value for the test statistcs is %4.4f\n",zval);
printf("The p-value of the test is %4.4f\n",p);


%1b

%Hints:1b ttest
%2a vartest2
%2b ttest2



%1.b. H0: u=5.5
%     H1: u>5.5




