#include <stdio.h>

int main()
{
    /* WRITE YOUR CODE HERE */

    int a, b, c, d, number;
    int fibonacci1, fibonacci2;
    char operator;
    int result = 0;

    scanf("%d %d %d %d %c %d", &a, &b, &c, &d, &operator, &number);
    fibonacci1 = a;
    fibonacci2 = b;
    for (int i = 2; i < number; ++i) {

        if (operator == '+') {
            result= (fibonacci1 * c) + (fibonacci2 * d);
        } else {
            result = (fibonacci1 * c) - (fibonacci2 * d);
        }
        fibonacci1 = fibonacci2;
        fibonacci2 = result;
    }
    printf("%d", result);


    return 0;
}
