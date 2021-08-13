% Grafica Psi al cuadrado de r con n=2

a0 = 0.0529; %Constante Radio de Borh en nm

%Funcion de densidad de proba. 


r=[0:0.01:4];
R= (4/a0.^3)*(r.^2).*exp(-2*(r)/a0); 





figure;
plot(r,R)
grid minor on 
title('|Psi(r)|^2 con n=2') 
xlabel('r nm');
ylabel('p(r)');