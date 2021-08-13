// Código para implementar algoritmo del trapecio 
// y de Simpson


#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;


double func(double);
double Trapecio(int, double, double);
double Simpson(int, double, double);

int main()
{
  int N; //Número de puntos
  double a, b;  // cotas inferior y superior de la integral
  double r1, r2;  //Técnicas de integración

  N = 101;
  a = 0.0;
  b = 1.0;

  r1 = Trapecio(N, a, b); // solución por medio de la R. del trapecio

  r2 = Simpson(N, a, b); // solución por medio de la R. de Simpson

  //Calcular error relativo
  cout << setprecision(20);
  double ExactSol = 0.5; //Editar según el valor de la integral a resolver
  cout << r1 << "\t" << r2 << "   " << fabs(ExactSol - r1)/ExactSol << "   "  << fabs(ExactSol - r2)/ExactSol <<  endl; 
  
  return 0;
}


//Definición de funciones Trapecio() y Simpson()

// Función a integrar
///////////////////////////////////////
double func(double x)
{
  double f;

  // Se edita la función a integrar
  f = x;

  return f;
}
///////////////////////////////////////


//////////////////////////////////////////////
// Regla del trapecio
double Trapecio(int N, double a, double b)
{
  double h;
  double x;
  double suma = 0.0;
  
  h = (b-a)/(N-1);

  for(int i = 2; i < N; i++)
    {
      x = a + (i-1)*h;
      suma += func(x)*h;
    }
  
  suma = suma + 0.5*h*func(a) + 0.5*h*func(b);
  
  return suma;
}
//////////////////////////////////////////////


//////////////////////////////////////////////
// Regla de Simpson
double Simpson(int N, double a, double b)
{
  double h;
  double x;
  double suma = 0.0;

  h = (b-a)/(N-1);

  //impares
  for(int i = 3; i < N; i=i+2)
    {
      x = a + (i-1)*h;
      suma += 2.0*func(x)*h;
    }

  //pares
   for(int i = 2; i < N; i=i+2)
    {
      x = a + (i-1)*h;
      suma += 4.0*func(x)*h;
    }

   suma = suma + func(a)*h + func(b)*h;
   suma = suma/3.0;
   
  return suma;
}
//////////////////////////////////////////////



