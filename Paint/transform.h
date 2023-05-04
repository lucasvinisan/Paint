#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "line.h"
#include "point.h"
#include "polygon.h"

#include <stdlib.h>
#include <math.h>
#include "transform.h"

char * intToString(int row, int column);
int charDigitToInt(char digit);
int stringToInt(const char *number, unsigned int length, unsigned int base);
int indexOfMatrix2D(int row, int column);

float * newMatrix2D();
float * pointToPoint2D(Point_Figure point);
void toIdentityMatrix2D(float * matrix);
void printMatrix2D(float * matrix);
void printPoint2D(float * point);
void multiplyMatrix2D(float * M, float * N);
void multiplyByPointMatrix2D(float * matrix, Point_Figure *point);
float * getTranslateMatrix(Point_Figure offset);
float * getRotateMatrix(float angle);
float * getScaleMatrix(Point_Figure scale);

#endif // TRANSFORM_H_INCLUDED
