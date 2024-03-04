


X1=[21.8, 22.6, 21.0, 19.7, 21.9, 21.6, 22.5, 23.1, 22.2, 20.1, 21.4, 20.5];
X2=[36.6, 35.2, 36.2, 34.0, 36.4, 36.1, 37.5, 38.0, 36.3, 35.9, 35.7, 34.9];

n1 = length(X1);
n2 = length(X2);
m1 = mean(X1);
m2 = mean(X2);
v1 = var(X1);
v2 = var(X2);



%a. At 5% significance level.
%H0.The null hypothesis H0: population variances are equal
%H1.The alternative hypothesis H1: population variances differ




alpha = input("\n\nPlease input the significance level(should be 0.05): ");
%alpha=0.05;

fprintf("\na)\n");
% Use vartest2 for variances test
[H, P, CI, STATS] = vartest2(X1, X2, 'Alpha', alpha);

if H == 0
    fprintf("\nThe null hypothesis is not rejected!\n");
    fprintf("The population variances are equal!\n");
else
    fprintf("\nThe null hypothesis is rejected!\n");
    fprintf("The population variances differ!\n");
end

f1 = finv(alpha/2, n1-1, n2-1);
f2 = finv(1-alpha/2, n1-1, n2-1);

fprintf("For the variances test we have:\n");
fprintf("The rejection region is (%.4f, %.4f) U (%.4f, %.4f)\n", -inf, f1, f2, inf);
fprintf("The P-value is %.4f\n", P);
fprintf("The statistics test value is %.4f\n", STATS.fstat);
fprintf("The value of H is %1f\n", H);



%b. The 95% confidence level of the average



if H == 0
    n = n1+n2-2;
    t = tinv(1-alpha/2, n);
    sp = sqrt(((n1-1)*v1 + (n2-1)*v2)/n);
    left = m1 - m2 - t*sp*sqrt(1/n1+1/n2);
    right = m1 - m2 + t*sp*sqrt(1/n1+1/n2);
else
    c = (v1/n1)/(v1/n1+v2/n2);
    n = c^2/(n1-1)+(1-c)^2/(n2-1);
    n = 1/n;
    t = tinv(1-alpha/2, n);
    left = m1-m2-t*sqrt(v1/n1+v2/n2);
    right = m1-m2+t*sqrt(v1/n1+v2/n2);
end
fprintf("\nb)\n");
fprintf("The 95 percent  confidence interval is: (%.4f, %.4f)\n\n\n", left, right);




