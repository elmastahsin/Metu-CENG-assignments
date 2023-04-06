
   #include <stdio.h>
#include <limits.h>
int main() {
    // your code goes here

   int n;
    scanf("%d", &n);
    int m;
    scanf("%d", &m);
    int matrix[n][n];

    double average = 0;
    double sum = 0;

    double maxAverage = INT_MIN;
    int r = 0;
    int c = 0;
    int size = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            scanf("%d", &matrix[i][j]);
        }
    }
    for (; m <= n; ++m) {
        for (int row = 0; row < (n - m) + 1; ++row) {
            for (int column = 0; column < (n - m) + 1; ++column) {
                for (int i = row; i < row + m; i++) {
                    for (int j = column; j < column + m; j++) {
                        sum += matrix[i][j];
                    }
                    average = sum / (m * m);
                    if (average > maxAverage) {
                        maxAverage = average;
                        r = row;
                        c = column;
                        size = m;
                    } else if (average == maxAverage) {
                        if (m > size) {
                            maxAverage = average;
                            r = row;
                            c = column;
                            size = m;
                        } else if (m == size) {
                            if (column < c) {
                                maxAverage = average;
                                r = row;
                                c = column;
                                size = m;
                            } else if (column == c) {
                                if (row < r) {
                                    maxAverage = average;
                                    r = row;
                                    c = column;
                                    size = m;
                                }
                            }
                        }
                    }
                }
                sum = 0;
            }
        }

    }
printf("%d %d %d",r+1,c+1,size);
    return 0;
}
