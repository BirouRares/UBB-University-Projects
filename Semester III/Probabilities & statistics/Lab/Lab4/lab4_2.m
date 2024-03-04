%lab 4 ex 2.2

N=input("Number of simulations between: ");
n=input("Enter the number of trials: ");
p=input("Probability of successs between 0 and 1: ");


U=rand(n,N);

X=sum(U<p);



k=0:n;
p_k=binopdf(k,n,p);

U_X=unique(X);

n_X=hist(X,length(U_X));
rel_freq=n_X/N;

plot(U_X,rel_freq,"*",k,p_k,"o");
