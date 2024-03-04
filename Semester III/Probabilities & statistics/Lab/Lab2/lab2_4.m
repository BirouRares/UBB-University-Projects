#we simulate 3 coin tosses

N=input("Give the number of simulation N=");
U=rand(3,N);
Y=(U<0.5); #if U less then 0.5 the Y =1[heads]
X=sum(Y);
clf;
hist(X);
