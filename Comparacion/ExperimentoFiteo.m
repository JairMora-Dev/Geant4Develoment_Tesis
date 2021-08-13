filename = 'Energiadepositada1.txt';
delimiterIn = '\t';
headerlinesIn = 1;
A = importdata(filename,delimiterIn,headerlinesIn);

%for k = [4]
 %  disp(A.colheaders{1, k})
  % disp(A.data(, k))
   %disp(' ')
%end

x = [A.data(1:999, 3)]
y = [A.data(1:999, 4)]

%integral = trapz(((x*0.00125)+0.000635), y)
%integral = trapz(x, y)
integral = trapz(y/1000)

%Tofit = plot(x,y);

%co_eff1 = polyfit(log(x), y, 4);
%plot(co_eff1);

a = 350
b = 0 
N= 1000

error = ((a - b)^3)/(12*(N^2))

%con 1000 error = 3.5729 con 69.829MeV
%con 10000 error = 0.035729 con 69



