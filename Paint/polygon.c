#include <stdlib.h>
#include "polygon.h"
#include "transform.h"

typedef struct PolygonLink {
    struct PointLink *next;
    Polygon_Figure polygon;
} PolygonLink;

void print_polygon(Polygon_Figure polygon) {
    Point_Figure aux;
    int length = lengthPointList(polygon.vertex_list);

    printf("{");
    for(int i = 0, j = 0; i < length; i++, j = i + 1)
    {
        getPointList(polygon.vertex_list, i, &aux);

        printf("(%.2f, %.2f)", aux.x, aux.y);

        if(j < length)
            printf(", ");
    }
    printf("}");
}

int isPolygonEquals(Polygon_Figure a, Polygon_Figure b) {
    if(lengthPointList(a.vertex_list) != lengthPointList(b.vertex_list)) return 0;

    int num_vertices = lengthPointList(a.vertex_list);
    if(num_vertices < 0) return 0;

    Point_Figure pa, pb;

    for(int i = 0; i < num_vertices; i++) {
        getPointList(a.vertex_list, i, &pa);
        getPointList(b.vertex_list, i, &pb);

        if(!isPointsEquals(pa, pb)) return 0;
    }

    return 1;
}

Polygon_Figure get_polygon(PointList *vertex_list) {
    Polygon_Figure polygon = { copyPointList(vertex_list) };
    return polygon;
}

Polygon_Figure get_polygon_copy(Polygon_Figure polygon) {
    Polygon_Figure copy = { copyPointList(polygon.vertex_list) };
    return copy;
}

Point_Figure polygon_get_centroid(Polygon_Figure polygon) {
    int i = 0;
    Point_Figure centroid = {0, 0}, aux;

    while(i < lengthPointList(polygon.vertex_list)) {
        getPointList(polygon.vertex_list, i, &aux);
        centroid.x += aux.x;
        centroid.y += aux.y;
        i++;
    }

    centroid.x /= i;
    centroid.y /= i;

    return centroid;
}

void rotate_polygon(Polygon_Figure *polygon, float angle) {
    Point_Figure center = polygon_get_centroid(*polygon);
    Point_Figure foward = {-center.x, -center.y};
    float * Tfoward = getTranslateMatrix(foward);
    float * rotate = getRotateMatrix(angle);
    float * Treturn = getTranslateMatrix(center);

    multiplyMatrix2D(Treturn, rotate);
    multiplyMatrix2D(Treturn, Tfoward);

    for(int i = 0; i < lengthPointList(polygon->vertex_list); i++)
    {
        multiplyByPointMatrix2D(Treturn, &polygon->vertex_list[i]);
    }

    free(Tfoward);
    Tfoward = NULL;

    free(rotate);
    rotate = NULL;

    free(Treturn);
    Treturn = NULL;
}

void translate_polygon(Polygon_Figure *polygon, Point_Figure offset) {
    float * translate = getTranslateMatrix(offset);

    for(int i = 0; i < lengthPointList(polygon->vertex_list); i++)
    {
        multiplyByPointMatrix2D(translate, &polygon->vertex_list[i]);
    }

    free(translate);
    translate = NULL;
}

void scale_polygon(Polygon_Figure *polygon, Point_Figure factor) {
    Point_Figure center = polygon_get_centroid(*polygon);
    Point_Figure foward = {-center.x, -center.y};
    float * Tfoward = getTranslateMatrix(foward);
    float * scale = getScaleMatrix(factor);
    float * Treturn = getTranslateMatrix(center);

    multiplyMatrix2D(Treturn, scale);
    multiplyMatrix2D(Treturn, Tfoward);

    for(int i = 0; i < lengthPointList(polygon->vertex_list); i++)
    {
        multiplyByPointMatrix2D(Treturn, &polygon->vertex_list[i]);
    }

    free(Tfoward);
    Tfoward = NULL;

    free(scale);
    scale = NULL;

    free(Treturn);
    Treturn = NULL;
}

PolygonList *newPolygonList() {
    PolygonList *list = (PolygonList *) malloc(sizeof(PolygonList *));

    if(*list != NULL)
        *list = NULL;

    return list;
}

PolygonList *copyPolygonList(PolygonList *list) {

    Polygon_Figure aux;
    PolygonList *copy = newPolygonList();

    for(int i = 0; i < lengthPolygonList(list); i++) {
        getPolygonList(list, i, &aux);
        addPolygonList(copy, aux);
    }

    return copy;
}

void clearPolygonList(PolygonList *list) {
    if(!isEmptyPolygonList(list)) {
        PolygonLink *current = *list, *aux = NULL;

        while(current != NULL) {
            aux = current;
            current = current->next;

            deletePointList(aux->polygon.vertex_list);
            free(aux);
            aux = NULL;
        }
    }

    *list = NULL;
}

void deletePolygonList(PolygonList *list) {
    clearPolygonList(list);
    free(list);
    list = NULL;
}

int isEmptyPolygonList(PolygonList *list) {
    if(*list == NULL) return 1;
    return 0;
}

int isNullPolygonList(PolygonList *list) {
    if(list == NULL) return 1;
    return 0;
}

int isNullOrEmptyPolygonList(PolygonList *list) {
    return isEmptyPointList(list) || isNullPointList(list);
}

void addToInitPolygonList(PolygonList *list, Polygon_Figure polygon) {
    PolygonLink *node = (PolygonLink *) malloc(sizeof(PolygonLink));
    node->polygon = polygon;
    node->next = *list;
    *list = node;
}

void addToEndPolygonList(PolygonList *list, Polygon_Figure polygon) {
    PolygonLink *node = (PolygonLink *) malloc(sizeof(PolygonLink));
    node->polygon = polygon;
    node->next = NULL;

    PolygonLink *aux = *list;

    while(aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = node;
}

int addPolygonList(PolygonList *list, Polygon_Figure polygon) {
    if(list == NULL) return -1;

    if(isEmptyPointList(list))
        addToInitPolygonList(list, get_polygon_copy(polygon));
    else
        addToEndPolygonList(list, get_polygon_copy(polygon));

    return 1;
}

int fixIndexPolygonList(PolygonList *list, int index) {
    int rest, term, negative = -index, length = lengthPolygonList(list);

    if(index < 0) {
        rest = index % length;
        term = negative == length ? 0 : length;

        index = rest == 0 ? 0 : rest + term;
    }

    return index;
}

int reverseIndexPolygonList(PolygonList *list, int index) {
    if(index > 0)
        return fixIndexPolygonList(list, -index);
    else
        return fixIndexPolygonList(list, index);
}

void removeToInitPolygonList(PolygonList *list) {
    PolygonLink *aux = *list;
    *list = aux->next;

    deletePointList(aux->polygon.vertex_list);
    free(aux);
    aux = NULL;
}

void removeToMiddlePolygonList(PolygonList *list, int index) {
    PolygonLink *current = *list, *prev = NULL;

    for(int i = 0; i < index && current != NULL; i++) {
        prev = current;
        current = current->next;
    }

    if(current != NULL) {
        prev->next = current->next;
        deletePointList(current->polygon.vertex_list);
        free(current);
        current = NULL;
    }
}

int removePolygonList(PolygonList *list, int index) {
    if(isNullOrEmptyPolygonList(list)) return -1;
    if(index > lengthPolygonList(list) || index < 0) return -1;

    if(index == 0)
        removeToInitPolygonList(list);
    else
        removeToMiddlePolygonList(list, index);

    return 1;
}

int lengthPolygonList(PolygonList *list) {
    if(isNullOrEmptyPolygonList(list)) return 0;

    int length = 0;
    PolygonLink *aux = *list;

    while(aux != NULL) {
        aux = aux->next;
        length++;
    }

    return length;
}

void copyDataPolygonList(PolygonList *list, int index, Polygon_Figure* copy) {

    PolygonLink *current = *list;

    for(int i = 0; i < index && current != NULL; i++)
        current = current->next;

    if(current != NULL) {
        *copy = current->polygon;
    }
}

int getPolygonList(PolygonList *list, int index, Polygon_Figure *copy) {
    if(isNullOrEmptyPolygonList(list)) return -1;
    if(index > lengthPolygonList(list)) return -1;

    copyDataPolygonList(list, index, copy);
    return 1;
}

int updatePolygonList(PolygonList *list, int index, Polygon_Figure polygon) {
    if(isNullOrEmptyLineList(list)) return -1;
    if(index > lengthLineList(list) || index < 0) return -1;

    PolygonLink *current = *list;

    for(int i = 0; i < index && current != NULL; i++)
        current = current->next;

    if(current != NULL) {
        current->polygon = polygon;
    }

    return 1;
}

int indexOfPolygonList(PolygonList *list, Polygon_Figure polygon) {
    if(isNullOrEmptyPolygonList(list)) return -1;

    int i = 0;
    PolygonLink *aux = *list;

    while(aux != NULL && !isPolygonEquals(polygon, aux->polygon)) {
        aux = aux->next;
        i++;
    }

    if(aux != NULL)
        return i;

    return -1;
}

void foreachPolygonList(PolygonList *list, PolygonCallback func) {
    if(!isNullPolygonList(list)) {
        PolygonLink *aux = *list;

        while(aux != NULL) {
            func(aux->polygon);
            aux = aux->next;
        }
    }
}
