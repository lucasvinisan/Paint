#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED

#include "point.h"

typedef struct Polygon_Figure{
    PointList *vertex_list;
} Polygon_Figure;

typedef struct PolygonLink **PolygonList;
typedef void(* PolygonCallback)(Polygon_Figure polygon);

/* warning: To print this fuction duplicate first point in last position */
void print_polygon(Polygon_Figure polygon);
int isPolygonEquals(Polygon_Figure a, Polygon_Figure b);
Polygon_Figure get_polygon(PointList *vertex_list);
Point_Figure polygon_get_centroid(Polygon_Figure polygon);

void rotate_polygon(Polygon_Figure *polygon, float angle);
void translate_polygon(Polygon_Figure *polygon, Point_Figure offset);
void scale_polygon(Polygon_Figure *polygon, Point_Figure factor);

PolygonList *newPolygonList();
PolygonList *copyPolygonList(PolygonList *list);
void clearPolygonList(PolygonList *list);
void deletePolygonList(PolygonList *list);
int isEmptyPolygonList(PolygonList *list);
int isNullPolygonList(PolygonList *list);
int isNullOrEmptyPolygonList(PolygonList *list);
int addPolygonList(PolygonList *list, Polygon_Figure polygon);
int removePolygonList(PolygonList *list, int index);
int lengthPolygonList(PolygonList *list);
int getPolygonList(PolygonList *list, int index, Polygon_Figure *copy);
int updatePolygonList(PolygonList *list, int index, Polygon_Figure polygon);
int indexOfPolygonList(PolygonList *list, Polygon_Figure polygon);
void foreachPolygonList(PolygonList *list, PolygonCallback func);

#endif // POLYGON_H_INCLUDED
