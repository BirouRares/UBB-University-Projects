#1
#a)
#P(x<=0)
#P(x>=0)=1-P(x<0) == (cont distribution) 1-P(x<=0)

#pdf f(x)=P(X=x)
#cdf F(x)=P(X<=x)

# P = normcdf (X, MU, SIGMA)

m=input("Enter MU:   ");
sigma=input("Enter sigma:   ");
P1=normcdf(0,m,sigma);
printf('P1(X)=%1.6f\n',P1);

P2=1-normcdf(0,m,sigma);

printf('P2(X)=%1.6f\n\n',P2);


#b)
#P(-1<=X<=1)  = F(1)-F(-1)
#P((X<=-1) U (X>=1)) = 1-P(-1<X<1)
#P(a<X<=b) =F(b)-F(a)    ==F(a<=X<=B)   ==P(a<X<b)

P1=normcdf(1,m,sigma);
P2=normcdf(-1,m,sigma);
P3=P1-P2;
printf('P3(X)=%1.6f\n',P3);
P4=1-P3;
printf('P4(X)=%1.6f\n',P3);

#c+d

a=input("Alfa:  ");
b=input("Beta:   ");

#F(x) = P(X<=x)= a belongs to [0,1]
#x=F^-1 (a)

#quantile=inv

P5=norminv(a,m,sigma);
P6=norminv(1-b,m,sigma);

printf('P5(X)=%1.6f\n',P5);
printf('P6(X)=%1.6f\n',P6);

#lipsa c....




