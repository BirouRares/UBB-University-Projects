%lab 4 ex2.1

N=input("Number of simulations between: ");
p=input("Probability of successs between 0 and 1: ");

U=rand(1,N);

X=(U < p);

U_X = [0 1];
n_X=hist(X,length(U_X));
rel_freq=n_X/N;
