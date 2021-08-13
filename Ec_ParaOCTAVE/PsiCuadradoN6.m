% Grafica Psi al cuadrado de r con n=2

a0 = 0.0529; %Constante Radio de Borh en nm

%Funcion de densidad de proba.
%R = @(x,y,z) (x.^2+ y.^2+ z.^2);
 

r= @(x,y,z) ((((1/a0).^(1.5)/(2160*sqrt(6))).^2).*(((720) - (300 * (sqrt(x.^2+y.^2+z.^2)/a0)) + ((100/3) 
.*(x.^2+y.^2+z.^2)/(a0.^2)) - ((25/18).*((x.^2+y.^2+z.^2).^(1.5)) / (a0.^3))  + ((5/216).*((x.^2+y.^2+z.^2).^2) 
/ (a0.^4)) - ((x.^2+y.^2+z.^2).^(2.5) /((a0.^5).*(7776)))).^2).*((exp(-sqrt(x.^2+y.^2+z.^2)/(6*a0))).^2)).*(x.^2+y.^2+z.^2);



[X,Y] = meshgrid(-2:0.01:2, -2:0.01:2); %Intervalos y numero de escala minima
Z= r(X,Y,0);


figure;
contour(X,Y,Z)
grid minor on
title('|Psi(r)|^2 con n=6')

%figure;
%surfc(X,Y,Z)
%title('|Psi(r)|^2 con n=6')
xlabel('x nm');
ylabel('y nm');