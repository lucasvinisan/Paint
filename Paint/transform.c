#include <stdlib.h>
#include <math.h>

#include "transform.h"

char * intToString(int row, int column) {
    int num_bytes = snprintf(NULL, 0, "%d%d", row, column) + 1;
    char * char_number = (char *) malloc(sizeof(num_bytes));

    snprintf(char_number, num_bytes, "%d%d", row, column);

    return char_number;
}

int charDigitToInt(char digit) {
    switch(digit)
    {
        case '0':
            return 0;

        case '1':
            return 1;

        case '2':
            return 2;

        case '3':
            return 3;

        case '4':
            return 4;

        case '5':
            return 5;

        case '6':
            return 6;

        case '7':
            return 7;

        case '8':
            return 8;

        case '9':
            return 9;

        case 'a':
            return 10;

        case 'b':
            return 11;

        case 'c':
            return 12;

        case 'd':
            return 13;

        case 'e':
            return 14;

        case 'f':
            return 15;

        case 'A':
            return 10;

        case 'B':
            return 11;

        case 'C':
            return 12;

        case 'D':
            return 13;

        case 'E':
            return 14;

        case 'F':
            return 15;

        default:
            return 0;
    }
}

int stringToInt(const char *number, unsigned int length, unsigned int base) {
    int num = 0;
    int is_negative_number = 0;
    char first_digit = number[0];

    if(first_digit == '-') is_negative_number = 1;

    for(int i = 0, j = length - 1; i < length; i++, j--)
    {
        num += charDigitToInt(number[i]) * (int) pow(base, j);
    }

    return is_negative_number ? -num : num;
}

int indexOfMatrix2D(int row, int column) {
    char * number = intToString(row, column);
    int vector_index = stringToInt(number, 2, 3);

    free(number);
    number = NULL;

    return vector_index;
}

float * newMatrix2D() {
     float * matrix = (float *) calloc(9, sizeof(float));
     return matrix;
}

void toIdentityMatrix2D(float * matrix) {
    int i_is_even, result_is_even;
     for(int i = 0; i < 9; i++) {
        i_is_even = (i % 2 == 0);
        result_is_even = (i / 2) % 2 == 0;
        matrix[i] = (i_is_even && result_is_even) ? 1 : 0;
     }
}

void printMatrix2D(float * matrix) {
     char endline;

     for(int i = 0, j = 1; i < 9; i++, j++) {
        endline = (j % 3 == 0) ? '\n' : ' ';
        printf("%.2f%c", matrix[i], endline);
     }
}

void printPoint2D(float * point) {
    for(int i = 0; i < 3; i++) printf("%.2f\n", point[i]);
}

float * pointToPoint2D(Point_Figure point) {
    float *point2D = (float*) malloc(3 * sizeof(float));

    point2D[0] = point.x;
    point2D[1] = point.y;
    point2D[2] = 1;

    return point2D;
}

void multiplyMatrix2D(float * M, float * N) {

    int i, j, k;
    float MN[9] = {0, 0, 0, 0, 0, 0, 0, 0};

    for(int row = 0; row < 3; row++) {
        for(int column = 0; column < 3; column++) {
            i = indexOfMatrix2D(row, column);

            for(int element = 0; element < 3; element++) {
                j = indexOfMatrix2D(row, element);
                k = indexOfMatrix2D(element, column);
                MN[i] += M[j] * N[k];
            }
        }
    }

    for(int i = 0; i < 9; i++) {
         M[i] = MN[i];
    }
}

void multiplyByPointMatrix2D(float * matrix, Point_Figure *point) {
    float sum;
    float result[3] = {0, 0, 0};
    float * point2D = pointToPoint2D(*point);

    for(int row = 0; row < 3; row++) {
        sum = 0;

        for(int column = 0; column < 3; column++) {
            sum += point2D[column] * matrix[indexOfMatrix2D(row, column)];
        }

        result[row] = sum;
    }
    point->x = result[0];
    point->y = result[1];

    free(point2D);
    point2D = NULL;
}

float * getTranslateMatrix(Point_Figure offset) {
    float * translate = newMatrix2D();
    toIdentityMatrix2D(translate);
    translate[2] = offset.x;
    translate[5] = offset.y;

    return translate;
}

float * getRotateMatrix(float angle) {
    float * rotate = newMatrix2D();
    toIdentityMatrix2D(rotate);

    float cosTheta = cosf(angle);
    float sinTheta = sinf(angle);

    rotate[0] = cosTheta;
    rotate[1] = sinTheta;
    rotate[3] = -sinTheta;
    rotate[4] = cosTheta;

    return rotate;
}

float * getScaleMatrix(Point_Figure factor) {
    float * scale = newMatrix2D();
    toIdentityMatrix2D(scale);

    scale[0] = factor.x;
    scale[4] = factor.y;

    return scale;
}
