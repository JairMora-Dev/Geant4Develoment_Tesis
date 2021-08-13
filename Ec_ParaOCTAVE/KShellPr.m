%#Para generar la campana
%ezsurfc('(4/0.529^3)*(x^2+y^2)*exp(-2*sqrt(x^2+y^2)/0.529)')

%#Para generar la curvas de nivel
%ezcontour('(4/0.529^3)*(x^2+y^2)*exp(-2*sqrt(x^2+y^2)/0.529)')

%#Para generar curvas de nivel con mapa de calor
hold on 
ezcontour('(4/0.0529^3)*(x^2+y^2)*exp(-2*sqrt(x^2+y^2)/0.0529)');
ezsurfc('(4/0.0529^3)*(x^2+y^2)*exp(-2*sqrt(x^2+y^2)/0.0529)');
hold off  

run
