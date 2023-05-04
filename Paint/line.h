#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED

#include "point.h"

typedef struct {
    Point_Figure start;
    Point_Figure end;
} Line_Figure;

typedef struct LineLink **LineList;
typedef void(* LineCallback)(Line_Figure element);

void print_line(Line_Figure line);
int isLinesEquals(Line_Figure a, Line_Figure b);
Line_Figure get_line_copy(Line_Figure line);
Point_Figure getCentroidLine(Line_Figure line);

void scale_line(Line_Figure *line, Point_Figure factor);
void rotate_line(Line_Figure *line, float angle);
void translate_line(Line_Figure *line, Point_Figure offset);

LineList *newLineList();
LineList *copyLineList(LineList *list);
void clearLineList(LineList *list);
void deleteLineList(LineList *list);
int isEmptyLineList(LineList *list);
int isNullLineList(LineList *list);
int isNullOrEmptyLineList(LineList *list);
int addLineList(LineList *list, Line_Figure data);
int removeLineList(LineList *list, int index);
int lengthLineList(LineList *list);
int getLineList(LineList *list, int index, Line_Figure *copy);
int updateLineList(LineList *list, int index, Line_Figure line);
int reverseIndexLineList(LineList *list, int index);
int indexOfLineList(LineList *list, Line_Figure data);
void foreachLineList(LineList *list, LineCallback func);

#endif // LINE_H_INCLUDED
