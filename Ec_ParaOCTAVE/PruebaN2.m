% Grafica Psi al cuadrado de r con n=2

a0 = 0.0529; %Constante Radio de Borh en nm

%Funcion de densidad de proba. 


r=[0:0.001:4];
R= ((r.^2)/(8*a0.^3)).*(2-(r)/a0).^2 .*(exp (-(r)/a0)); 





figure;
plot(r,R)
grid minor on 
title('|Psi(r)|^2 con n=2') 
xlabel('r nm');
ylabel('p(r)');