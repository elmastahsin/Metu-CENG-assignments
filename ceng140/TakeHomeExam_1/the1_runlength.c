#include <stdio.h>

int main()
{
    /* WRITE YOUR CODE HERE */
       int count = 1;
       char string, temp;
       scanf("%c", &string);

       temp = string;

       while (!(string == '\n')) {
           scanf("%c", &string);
           if (string == temp) {
               count++;
           } else {
               printf("%d%c", count, temp);
               count = 1;
           }
           temp = string;
       }

       return 0;
}
