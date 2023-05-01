#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

typedef struct {
    float x;
    float y;
} Point_Figure;

typedef struct PointLink **PointList;
typedef void(* PointCallback)(Point_Figure element);

void print_point(Point_Figure point);
int isPointsEquals(Point_Figure a, Point_Figure b);

PointList *newPointList();
PointList *copyPointList(PointList *list);
void clearPointList(PointList *list);
void deletePointList(PointList *list);
int isEmptyPointList(PointList *list);
int isNullPointList(PointList *list);
int isNullOrEmptyPointList(PointList *list);
int addPointList(PointList *list, Point_Figure point);
int reverseIndexPointList(PointList *list, int index) ;
int removePointList(PointList *list, int index);
int lengthPointList(PointList *list);
int getPointList(PointList *list, int index, Point_Figure *copy);
int indexOfPointList(PointList *list, Point_Figure point);
void foreachPointList(PointList *list, PointCallback func);

#endif // POINT_H_INCLUDED
