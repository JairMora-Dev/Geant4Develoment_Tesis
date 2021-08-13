% Grafica Psi al cuadrado de r con n=2

a0 = 0.0529; %Constante Radio de Borh en nm

%Funcion de densidad de proba.

r=[0:0.001:6]; 

R =  (((((1/a0).^(1.5)/(2160*sqrt(6))).^2).*(((720) - (300 * (r)/a0)) + ((100/3) 
.*(r.^2)/(a0.^2)) - ((25/18).*((r).^(3)) / (a0.^3))  + ((5/216).*((r).^4) 
/ (a0.^4)) - ((r).^(5) /((a0.^5).*(7776)))).^2).*((exp(-(r)/(6*a0))).^2)).*(r.^2) .*(4*pi);






figure;
plot(r, R)
grid minor on
title('|Psi(r)|^2 con n=6')

xlabel('r nm');
ylabel('p(r)');