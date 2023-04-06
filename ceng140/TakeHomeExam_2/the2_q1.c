#include <stdio.h>

int main() {
    // your code goes here
    
   int n, m;


    scanf("%d", &n);
    scanf("%d",&m);
    int I[n];
    int K[m];

    for (int i = 0; i < n; i++) {

        scanf("%d", &I[i]);
    }
    for (int i = 0; i < m; i++) {

        scanf("%d", &K[i]);
    }
    int l = n - m + 1;
    int O[l];
    for (int i = 0; i < l; i++) {
        int result=0;
        for (int j = 0; j < m; j++) {
            result += I[j + i] * K[j];
        }
        O[i] = result;
        printf("%d ",O[i]);
    }
    
    
    
    
    
    
    
    
    
    
    return 0;
}