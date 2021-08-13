% Grafica Psi al cuadrado de r con n=2

a0 = 0.0529; %Constante Radio de Borh en nm

%Funcion de densidad de proba. 
%R = @(x,y,z) (x.^2+ y.^2+ z.^2);
r= @(x,y,z) ((x.^2+ y.^2+ z.^2)/(8*a0.^3)).*(2-(sqrt(x.^2+ y.^2+ z.^2)/a0)).^2 .*(exp (-sqrt((x.^2+ y.^2+ z.^2))/a0)); 
[X,Y] = meshgrid(-2:0.001:2, -2:0.001:2); %Intervalos y numero de escala minima
Z= r(X,Y,0);


%figure;
%contour(X,Y,Z)
%grid minor on 
%title('|Psi(r)|^2 con n=2') 

figure;
surfc(X,Y,Z)
title('|Psi(r)|^2 con n=2') 
xlabel('x nm');
ylabel('y nm');
