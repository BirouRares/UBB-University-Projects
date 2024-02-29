#2C
p1=binopdf(0,3,0.5);
printf('P(X=0)= %1.6f\n',p1);

p2=1-binopdf(1,3,0.5);
printf('P(X)!=%1.6f\n',p2);

#2D

p3=binopdf(2,3,0.5);
printf('P(X<=2)=%1.6f\n',p3);

p4=binocdf(1,3,0.5);
printf('P(X<2)=%1.6f\n',p4);

p5=1-binocdf(0,3,0.5);
printf('P(X>=1)=%1.6f\n',p5);

p6=1-binocdf(1,3,0.5);
printf('P(X>1)=%1.6f\n',p6);



