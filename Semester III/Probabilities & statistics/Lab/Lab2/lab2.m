#help pdf
#help cdf


#we are solving ex.2
#we plot the pdf&cdf of the binomial

n=input("Give nb of trials n=");   #n - natural number
p=input("Give the prob. of success p=");  # p is between 0 AND 1

x=0:1:n; # number of successes in n trials
px=binopdf(x,n,p);
plot(x,px,'*r')
hold on   # keep the plot that is above in the same window

xx=0:0.01:n;  # continues plot
cx=binocdf(xx,n,p);
plot(xx,cx,'g')

#HW: find how "legend" works & put a legend for graphs in Application
