#include <stdio.h>

int main()
{
    /* WRITE YOUR CODE HERE */
    double x, derivative, n, a;
      
     double f = 0.0;
      
      scanf("%lf %lf %lf", &x, &derivative, &n);
    double xPow ;
      for (int j = n; j >= 0; j--)
      {
          xPow = 1;
          
          n = j;

          scanf("%lf", &a);
          
          if (a == 0)
          {
              continue;
          }
          
          for (int i = (int) derivative; i > 0; i--)
          {
              a = a * n;
              n--;

          }
          
          for (int i = 0; i < n; ++i)
          {
              xPow *= x;
          }
          f += a * xPow;
      }

      printf("%.3lf", f);
  
    return 0;
}
