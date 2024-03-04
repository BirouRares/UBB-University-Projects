%lab 4 ex 2.3

N=input("Number of simulations between: ");
p=input("Probability of successs between 0 and 1: ");

X=zeros(1,N);

for i=1:N
  X(i)=0;
  while rand()>=p
      X(1)=X(i)+1;
  endwhile

endfor

k=0:20;

p_k=geopdf (k,p);
U_X=unique(X);

n_X=hist(X,length(U_X));
rel_freq=n_X/N;
plot(U_X,rel_freq,"*",k,p_k,"o");

%for ex2.4  binomial for the bernuli
