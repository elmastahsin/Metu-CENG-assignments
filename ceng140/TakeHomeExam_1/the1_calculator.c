#include <stdio.h>

int main()
{
    /* WRITE YOUR CODE HERE */
    double firstNumber;

    double secondNumber;

    char arithmeticOperator;


        scanf("%lf %c %lf", &firstNumber, &arithmeticOperator, &secondNumber);

        double result;

        if (arithmeticOperator == '+') 
        {
            result = firstNumber + secondNumber;
        } 
        else if (arithmeticOperator == '-')
        {
            result = firstNumber - secondNumber;
        } 
        else if (arithmeticOperator == '*') 
        {
            result = firstNumber * secondNumber;
        }
        else 
        {
            result = firstNumber / secondNumber;
        }

        printf("%.3lf", result);
    return 0;
    
}
