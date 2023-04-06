#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int readLine(char *buffer, unsigned bufferSize) {
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


int main() {
    char variable[100][100];
    int value[100];

    char lines[100][100];
    char eachLine[100];

    int line = 0;

    char *tkn;

    int size = 0;


    while (1) {
        char buf[100];

        int rv = readLine(buf, 100);

        if (rv == 0) {
            return 0;
        }
        if (rv == -1) {
            break;
        }
        strcpy(lines[line], buf);
        line++;

        int exitValue = strncmp("exit", buf, 4);
        if (exitValue == 0) {
            break;
        }
    }
    int row = 0;
    while (row < line) {

        strcpy(eachLine, lines[row]);

        tkn = strtok(eachLine, " ");


        if (strcmp(tkn, "set") == 0) {
            tkn = strtok(NULL, " ");
            int hasVariable  = 1;

            for (int j = 0; j < size; ++j) {
                if (strcmp(tkn, variable[j]) == 0) {
                    tkn = strtok(NULL, " ");
                    value[j] = atoi(tkn);
                    hasVariable  = 0;
                }
            }
            if (hasVariable ) {
                strcpy(variable[size], tkn);
                tkn = strtok(NULL, " ");
                value[size] = atoi(tkn);
                size++;
            }
        }
        if (strcmp(tkn, "add") == 0) {
            char *firstAddVariable;
            char *secondAddVariable;
            int firstAddValue;
            int secondAddValue;


            tkn = strtok(NULL, " ");
            firstAddVariable = tkn;
            int hasVariable  = 1;
            for (int j = 0; j < size; ++j) {
                if (strcmp(firstAddVariable, variable[j]) == 0) {
                    firstAddValue = value[j];
                    hasVariable  = 0;
                }
            }
            if (hasVariable ) {
                strcpy(variable[size], firstAddVariable);

                value[size] = 0;
                size++;
            }
            tkn = strtok(NULL, " ");
            secondAddVariable = tkn;
            hasVariable  = 1;
            for (int j = 0; j < size; ++j) {
                if (strcmp(secondAddVariable, variable[j]) == 0) {
                    secondAddValue = value[j];
                    hasVariable  = 0;
                }
            }
            if (hasVariable ) {
                strcpy(variable[size], secondAddVariable);
                value[size] = 0;
                size++;
            }
            int sum = firstAddValue + secondAddValue;
            if (sum > 99) {
                sum = 99;
            }
            for (int a = 0; a < size; a++) {
                if (strcmp(firstAddVariable, variable[a]) == 0) {

                    value[a] = sum;
                    break;
                }
            }
        }
        if (strcmp(tkn, "sub") == 0) {
            char *firstSubVariable;
            char *secondSubVariable;
            int firstSubValue = 0;
            int secondSubValue = 0;
            tkn = strtok(NULL, " ");
            firstSubVariable = tkn;
            int hasVariable  = 1;
            for (int j = 0; j < size; ++j) {
                if (strcmp(firstSubVariable, variable[j]) == 0) {
                    firstSubValue = value[j];
                    hasVariable  = 0;
                }
            }
            if (hasVariable ) {
                strcpy(variable[size], firstSubVariable);
                value[size] = 0;
                size++;
            }
            tkn = strtok(NULL, " ");
            secondSubVariable = tkn;
            hasVariable  = 1;
            for (int j = 0; j < size; ++j) {
                if (strcmp(secondSubVariable, variable[j]) == 0) {
                    secondSubValue = value[j];
                    hasVariable  = 0;
                    break;
                }
            }
            if (hasVariable ) {
                strcpy(variable[size], secondSubVariable);
                value[size] = 0;
                size++;
            }
            int sub = firstSubValue - secondSubValue;
            if (sub <= 0) {
                sub = 0;
            }
            for (int k = 0; k < size; k++) {
                if (strcmp(firstSubVariable, variable[k]) == 0) {
                    value[k] = sub;
                    break;
                }
            }
        }
        if (strcmp(tkn, "goback") == 0) {
            int goBackLine = 0;

            tkn = strtok(NULL, " ");
            goBackLine = atoi(tkn);

            char *firstVariable = strtok(NULL, " ");
            int firstValue = 0;


            char *secondVariable = strtok(NULL, " ");
            int secondValue = 0;
            int hasVariable  = 1;
            for (int j = 0; j < size; ++j) {
                if (strcmp(firstVariable, variable[j]) == 0) {
                    firstValue = value[j];
                    hasVariable  = 0;
                }
            }
            if (hasVariable ) {
                strcpy(variable[size], firstVariable);
                value[size] = 0;
                size++;
            }

            hasVariable  = 1;

            for (int j = 0; j < size; ++j) {
                if (strcmp(secondVariable, variable[j]) == 0) {
                    secondValue = value[j];
                    hasVariable  = 0;
                    break;
                }
            }
            if (hasVariable ) {
                strcpy(variable[size], secondVariable);
                value[size] = 0;
                size++;
            }

            if (firstValue < secondValue) {
                row = row - goBackLine;
                continue;
            }
        }
        if (strcmp(tkn, "show") == 0) {
            tkn = strtok(NULL, " ");
            int hasVariable  = 1;
            for (int i = 0; i < size; ++i) {
                if (strcmp(tkn, variable[i]) == 0) {
                    printf("%s = %d\n", tkn, value[i]);
                    hasVariable  = 0;
                    break;
                }

            }
            if (hasVariable ) {
                strcpy(variable[size], tkn);
                value[size] = 0;
                printf("%s = %d\n", tkn, value[size]);
                size++;
            }
        }

        row++;
    }

    return 0;
}