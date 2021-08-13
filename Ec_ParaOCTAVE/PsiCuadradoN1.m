% Grafica Psi al cuadrado de r con n=1

a0 = 0.0529; %Constante Radio de Borh en nm
r= @(x,y,z) (4/a0.^3)*(x.^2+y.^2+z.^2).*exp(-2*sqrt(x.^2+y.^2+z.^2)/a0); %Funcion de densidad de proba. 
[X,Y] = meshgrid(-2:0.001:2, -2:0.001:2); %Intervalos y numero de escala minima
Z= r(X,Y,0);


%figure;
%contour(X,Y,Z)
%grid minor on 
%title('|Psi(r)|^2 con n=1') 

figure(1);
surfc(X,Y,Z)
title('|Psi(r)|^2 con n=1')
xlabel('x nm');
ylabel('y nm');

