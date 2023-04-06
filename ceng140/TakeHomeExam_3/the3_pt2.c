#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int readLineDelimeter(char *buffer, unsigned bufferSize) {
    unsigned nextIndex = 0;

    while (1) {
        if (nextIndex == bufferSize) {
            return 0; // Out of buffer. Indicate error.
        }

        char c;
        int rv = scanf("%c", &c);

        if (rv == EOF) {
            buffer[nextIndex] = '\0';
            return -1; // Indicate that the end of the input was hit.
        }

        if (rv != 1) // Some other unknown error. Unlikely to happen.
        {
            return 0; // Indicate error.
        }

        // Successfully read ``c'' at this point.

        if (c == '\n') {
            buffer[nextIndex] = '\0';
            return +1; // Indicate that a newline was hit.
        } else {
            buffer[nextIndex] = c;
            nextIndex++;
        }
    }
}

int readLineString(char *buffer, unsigned bufferSize) {
    unsigned nextIndex = 0;

    while (1) {
        if (nextIndex == bufferSize) {
            return 0; // Out of buffer. Indicate error.
        }

        char c;
        int rv = scanf("%c", &c);

        if (rv == EOF) {
            buffer[nextIndex] = '\0';
            return -1; // Indicate that the end of the input was hit.
        }

        if (rv != 1) // Some other unknown error. Unlikely to happen.
        {
            return 0; // Indicate error.
        }

        // Successfully read ``c'' at this point.

        if (c == '\n') {
            continue;// Indicate that a newline was hit.
        } else {
            buffer[nextIndex] = c;
            nextIndex++;
        }
    }
}

char *substr(const char *src, int m, int n) {
    // get the length of the destination string
    int len = n - m;

    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char *) malloc(sizeof(char) * (len + 1));

    // extracts characters between m'th and n'th index from source string
    // and copy them into the destination string
    for (int i = m; i < n && (*(src + i) != '\0'); i++) {
        *dest = *(src + i);
        dest++;
    }

    // null-terminate the destination string
    *dest = '\0';

    // return the destination string
    return dest - len;
}
void sort(char array[][100], int n) {
    int i, j;
    char temp[100];

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (strlen(array[j]) > strlen(array[j + 1])) {
                strcpy(temp, array[j]);
                strcpy(array[j], array[j + 1]);
                strcpy(array[j + 1], temp);
            }
        }
    }
}
int main() {
    char string[1000];
    char sentence[100][1000];

    char startDel[20];
    char endDel[20];

    readLineDelimeter(startDel, 1000);
    readLineDelimeter(endDel, 1000);
    readLineString(string, 1000);
    char delimetedWords[100][100];
    int DelimeterSize=0;
    int startLen = strlen(startDel);

    char part[100];
    int s = 0;
    while (1) {
        char *start = strstr(string, startDel);
        int indexOfStartDElimeter = (int) (start - string);

        char *end = strstr(string, endDel);
        int indexOfEndDElimeter = (int) (end - string);

        int i = 0;

        char *currentPointer = start + startLen;
        int size = end - (start + startLen);

        if (strlen(string) > 0) {
            strcpy(sentence[s], substr(string, 0, (indexOfStartDElimeter)));
            s++;
        }

        while (i < size) {

            part[i] = *(currentPointer + i);

            i++;
        }
        part[i] = '\0';
        strcpy(delimetedWords[DelimeterSize], part);
        DelimeterSize++;
        strcpy(sentence[s], part);
        s++;
        
        int stringLen=strlen(string);
        if (stringLen > 0) {
            strcpy(string, substr(string, (indexOfEndDElimeter + strlen(endDel)), strlen(string)));
        }

        if (strstr(string, startDel) == NULL) {
            strcpy(sentence[s], string);
            s++;
            break;
        }

    }
    sort(delimetedWords, DelimeterSize);
    for (int i = 0; i < DelimeterSize; ++i) {
        printf("%s\n", delimetedWords[i]);
    }

    for (int i = 0; i < s; ++i) {
        printf("%s", sentence[i]);
    }
    printf("\n");
    return 0;
}