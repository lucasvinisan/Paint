#include <stdlib.h>
#include "point.h"

typedef struct PointLink {
    struct PointLink *next;
    Point_Figure point;
} PointLink;

void print_point(Point_Figure point) {
    printf("(%.2f, %.2f)", point.x, point.y);
}

int isPointsEquals(Point_Figure a, Point_Figure b) {
    if(a.x == b.x && a.y == b.y) return 1;
    return 0;
}

Point_Figure get_point_copy(Point_Figure point) {
    Point_Figure copy = {point.x, point.y};
    return copy;
}

PointList *newPointList() {
    PointList list = (PointList *) malloc(sizeof(PointList *));

    if(*list != NULL)
        *list = NULL;

    return list;
}

PointList *copyPointList(PointList *list) {
    Point_Figure aux;
    PointList *copy = newPointList();

    for(int i = 0; i < lengthPointList(list); i++) {
        getPointList(list, i, &aux);
        addPointList(copy, aux);
    }

    return copy;
}

void clearPointList(PointList* list) {
    if(!isEmptyPointList(list)) {
        PointLink *current= *list, *aux = NULL;

        while(current != NULL) {
            aux = current;
            current = current->next;
            free(aux);
            aux = NULL;
        }
    }

    *list = NULL;
}

void deletePointList(PointList *list) {
    clearPointList(list);
    free(list);
    list = NULL;
}

int isEmptyPointList(PointList *list) {
    if(*list == NULL) return 1;
    return 0;
}

int isNullPointList(PointList *list) {
    if(list == NULL) return 1;
    return 0;
}

int isNullOrEmptyPointList(PointList *list) {
    return isEmptyPointList(list) || isNullPointList(list);
}

void addToInitPointList(PointList *list, Point_Figure point) {
    PointLink *node = (PointLink *) malloc(sizeof(PointLink));
    node->point = point;
    node->next = *list;
    *list = node;
}

void addToEndPointList(PointList *list, Point_Figure point) {
    PointLink *node = (PointLink *) malloc(sizeof(PointLink));
    node->point = point;
    node->next = NULL;

    PointLink *aux = *list;

    while(aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = node;
}

int addPointList(PointList *list, Point_Figure point) {
    if(list == NULL) return -1;

    if(isEmptyPointList(list))
        addToInitPointList(list, get_point_copy(point));
    else
        addToEndPointList(list, get_point_copy(point));

    return 1;
}

int fixIndexPointList(PointList *list, int index) {
    int rest, term, negative = -index, length = lengthPointList(list);

    if(index < 0) {
        rest = index % length;
        term = negative == length ? 0 : length;

        index = rest == 0 ? 0 : rest + term;
    }

    return index;
}

int reverseIndexPointList(PointList *list, int index) {
    if(index > 0)
        return fixIndexPointList(list, -index);
    else
        return fixIndexPointList(list, index);
}

void removeToInitPointList(PointList *list) {
    PointLink *aux = *list;
    *list = aux->next;
    free(aux);
    aux = NULL;
}

void removeToMiddlePointList(PointList *list, int index) {
    PointLink *current = *list, *prev = NULL;

    for(int i = 0; i < index && current != NULL; i++) {
        prev = current;
        current = current->next;
    }

    if(current != NULL) {
        prev->next = current->next;
        free(current);
        current = NULL;
    }
}

int removePointList(PointList *list, int index) {
    if(isNullOrEmptyPointList(list)) return -1;
    if(index > lengthPointList(list) || index < 0) return -1;

    if(index == 0)
        removeToInitPointList(list);
    else
        removeToMiddlePointList(list, index);

    return 1;
}

int lengthPointList(PointList *list) {
    if(isNullOrEmptyPointList(list)) return 0;

    int length = 0;
    PointLink *aux = *list;

    while(aux != NULL) {
        aux = aux->next;
        length++;
    }

    return length;
}

void copyDataPointList(PointList *list, int index, Point_Figure* copy) {

    PointLink *current = *list;

    for(int i = 0; i < index && current != NULL; i++)
        current = current->next;

    if(current != NULL) {
        *copy = current->point;
    }
}

int getPointList(PointList *list, int index, Point_Figure *copy) {
    if(isNullOrEmptyPointList(list)) return -1;
    if(index > lengthPointList(list) || index < 0) return -1;

    copyDataPointList(list, index, copy);
    return 1;
}

int indexOfPointList(PointList *list, Point_Figure point) {
    if(isNullOrEmptyPointList(list)) return -1;

    int i = 0;
    PointLink *aux = *list;

    while(aux != NULL && !isPointsEquals(point, aux->point)) {
        aux = aux->next;
        i++;
    }

    if(aux != NULL)
        return i;

    return -1;
}

void foreachPointList(PointList *list, PointCallback func) {
    if(!isNullOrEmptyPointList(list)) {

        PointLink *aux = *list;

        while(aux != NULL) {
            func(aux->point);
            aux = aux->next;
        }
    }
}
