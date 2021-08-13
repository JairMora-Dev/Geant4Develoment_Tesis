filename = 'Energiadepositada1.txt';
delimiterIn = '\t';
headerlinesIn = 1;
A = importdata(filename,delimiterIn,headerlinesIn);

%for k = [4]
 %  disp(A.colheaders{1, k})
  % disp(A.data(, k))
   %disp(' ')
%end

x = [(A.data(1:999, 3)*0.00127+0.000635)]
y = [A.data(1:999, 4)]


c = spline(x,y);

f = @(x) ppval(c,x);
%xs = linspace(0,1.27);
xs = 0:0.00254:1.27;
a1 = 0:0.00381:1.27;
a2 = 0:0.00508:1.27;
a3 = 0:0.00635:1.27;
a4 = 0:0.00127:1.27;
a5 = 0:0.000127:1.27;

ys = f(xs);
y1 = f(a1);
y2 = f(a2);
y3 = f(a3);
y4 = f(a4);
y5 = f(a5);

plot(x,y,xs,ys);

%q = trapz(((x*0.00125)+0.000635), y)
q = trapz(a5,y5)/1.27
q1 = trapz(xs,ys)/1.27
q2 = trapz(a1,y1)/1.27
q3 = trapz(a2,y2)/1.27
q4 = trapz(a3,y3)/1.27
q5 = trapz(a4,y4)/1.27


%Construccion segunda derivada para el error asociado
DeltaX = 0.00127;
 
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
      TotalDerivada = Derivada / 1000;
    end
%.....................................................


errorq = (1.27^(3))/(12)*(0.127^(2)) *(TotalDerivada)
errorq1 = (1.27^(3))/(12)*(2.54^(2)) *(TotalDerivada)
errorq2 = (1.27^(3))/(12)*(3.81^(2)) *(TotalDerivada)
errorq3 = (1.27^(3))/(12)*(5.08^(2)) *(TotalDerivada)
errorq4 = (1.27^(3))/(12)*(6.35^(2)) *(TotalDerivada)
errorq5 = (1.27^(3))/(12)*(1.27^(2)) *(TotalDerivada)

ErroPorce_q = (q*errorq)/100
ErroPorce_q1 = (q1*errorq1)/100
ErroPorce_q2 = (q2*errorq2)/100
ErroPorce_q3 = (q3*errorq3)/100
ErroPorce_q4 = (q4*errorq4)/100
ErroPorce_q5 = (q5*errorq5)/100





%x1 = 0
%x2 = 1.27

%[q_quad, ier, nfun, err]=quad(f,x1,x2)

%Energia=q_quad/1.27













