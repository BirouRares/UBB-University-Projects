#X_ Bino(nr of ties:3, Probability:50%= 0.5)
#
#
x=0:1:3; #val of x are 0 1 2 3
px=binopdf(x,3,0.5);
plot(x,px,'*r')
hold on   # keep the plot that is above in the same window

xx=0:0.01:3;  # continues plot
cx=binocdf(xx,3,0.5);
plot(xx,cx,'g')


