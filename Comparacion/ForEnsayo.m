filename = 'Energiadepositada1.txt';
delimiterIn = '\t';
headerlinesIn = 1;
A = importdata(filename,delimiterIn,headerlinesIn);


x = [(A.data(1:999, 3)*0.00127+0.000635)]
y = [A.data(1:999, 4)]

 %Energia = 0;
          %for i = 1:999
            %Energia = Energia + y(i);
            %TotalEnergia = Energia/1000
          %end

DeltaX = 0.00127;
  
%For de ensayo para la energia
 
  %DerivadaN3 = (y(4:4) - (2 * y(3:3))  + y(2:2)) / DeltaX
  
  for k = 3:998
          ParteDerivada1 = y(k+1:k+1);
          ParteDerivada2 = (2 * y(k:k));  
          ParteDerivada3 =  y(k-1:k-1);
          
          SegundaDerivada(k,1) = (ParteDerivada1 - ParteDerivada2 + ParteDerivada3) / DeltaX;
  end
              
  Derivada = 0;
    for i = 1:998
      Derivada = Derivada + SegundaDerivada(i);
      %TotalDerivada = Derivada;
    end

  
  
  
  

 
 

  

  