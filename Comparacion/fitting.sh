#Curve fitting with gnuplot

#Define funtion

f(x) = b*x + c*(x**2) + d*(x**3) + e*(x**4);

#initial guess
b = 100.25;
c = 436.42;
d = -2.2126exp(06);
e = 9.6694exp(08);

#perform fit

fit f(x) "Energiadepositada1.txt" u (($3*0.00127)+0.000635):($4) via b,c,d,e

#plot results
plot "Energiadepositada1.txt" u (($3*0.00127)+0.000635):($4), f(x)
