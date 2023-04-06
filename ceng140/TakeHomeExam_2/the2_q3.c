#include <stdio.h>
#include <limits.h>

void assignDashToFrame(int row, int column, int canvas[row + 1][column + 1][2]) {
    
    for (int i = row; i > 0; i--) {
        for (int j = 1; j <= column; j++) {
            canvas[i][j][0] = '-';
            canvas[i][j][1] = INT_MAX;
        }
    }
}

void countCircle(int row, int column, int circleNumber, int canvas[row + 1][column + 1][2],
                 int statistics[circleNumber][4]) {
                     
    for (int j = row; j > 0; --j) {
        for (int k = 1; k <= column; ++k) {
            for (int i = 0; i < circleNumber; ++i) {

                if (canvas[j][k][0] == statistics[i][3]) {
                    statistics[i][0]++;
                }

            }

        }
    }
}


void printCircle(int row, int column, int canvas[row + 1][column + 1][2]) {
    for (int i = row; i > 0; i--) {

        for (int j = 1; j <= column; j++) {
            printf("%c%c", (char) canvas[i][j][0], (char) canvas[i][j][0]);

        }
        printf("\n");
    }
}

void printStatistics(int writeStatistics, int circleNumber, int statistics[circleNumber][4]) {
    if (writeStatistics) {
        for (int i = circleNumber - 1; i >= 0; i--) {

            printf("%d %d %d", statistics[i][0], statistics[i][1],
                   statistics[i][2] - (statistics[i][0] + statistics[i][1]));
            printf("\n");
        }
    }
}

void countOutsideOfFrame(int radius, int circleCount, int statistics[circleCount][4]) {
    
    for (int i = 0; i <= radius + radius; ++i) {
        for (int j = 0; j <= radius + radius; ++j) {
            int drawCircle = (((radius - j) * (radius - j)) + ((radius - i) * (radius - i)));
            if (drawCircle <= radius * radius) {
                statistics[circleCount][2]++;
            }
        }
    }
}


void assignLetterToFrame(int row, int column, int circleNumber, int canvas[row + 1][column + 1][2],
                         int statistics[circleNumber][4],
                         char letter, int radius, int depth, int x, int y) {
                             
    for (int i = row; i > 0; --i) {
        for (int j = 1; j <= column; ++j) {
            int drawCircle = (((x - j) * (x - j)) + ((y - i) * (y - i)));
            if (drawCircle <= radius * radius && canvas[i][j][1] > depth) {
                for (int k = circleNumber - 1; k >= 0; --k) {
                    if (canvas[i][j][0] == statistics[k][3]) {
                        statistics[k][1]++;
                    }
                }
                canvas[i][j][0] = letter;
                canvas[i][j][1] = depth;
            } else if (drawCircle <= radius * radius && canvas[i][j][1] < depth) {
                for (int k = circleNumber - 1; k >= 0; --k) {

                    if (letter == statistics[k][3]) {
                        statistics[k][1]++;
                    }
                }
            }
        }
    }
}

int main() {

    // your code goes here
    int row;
    int column;
    int circleNumber;
    int writeStatistics;

    scanf("%d %d %d %d", &column, &row, &circleNumber, &writeStatistics);

    int canvas[row + 1][column + 1][2];
    
    assignDashToFrame(row, column, canvas);

    char letter;
    int x, y, radius, depth;
    int statistics[circleNumber][4];
    for (int circleCount = circleNumber - 1; 0 <= circleCount; --circleCount) {


        scanf(" %c %d %d %d %d", &letter, &x, &y, &radius, &depth);
        
        statistics[circleCount][0] = 0;
        statistics[circleCount][1] = 0;
        statistics[circleCount][2] = 0;
        statistics[circleCount][3] = letter;



        countOutsideOfFrame(radius, circleCount, statistics);
        

        assignLetterToFrame(row, column, circleNumber, canvas, statistics, letter, radius, depth, x, y);
        

    }

    printCircle(row, column, canvas);


    countCircle(row, column, circleNumber, canvas, statistics);
    
    
    printStatistics(writeStatistics, circleNumber, statistics);


    return 0;

}