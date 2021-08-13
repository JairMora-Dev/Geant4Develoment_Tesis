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








