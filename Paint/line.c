#include <stdlib.h>
#include "line.h"
#include "transform.h"

typedef struct LineLink {
    struct LineLink *next;
    Line_Figure line;
} LineLink;

void print_line(Line_Figure line) {
    printf("[(%.2f, %.2f), (%.2f, %.2f)]",
           line.start.x, line.start.y,
           line.end.x, line.end.y
    );
}

int isLinesEquals(Line_Figure a, Line_Figure b) {
    if(isPointsEquals(a.start, b.start) &&
       isPointsEquals(a.end, b.end)) return 1;
    return 0;
}

Line_Figure get_line_copy(Line_Figure line) {
    Point_Figure start_copy = {line.start.x, line.start.y};
    Point_Figure end_copy = {line.end.x, line.end.y};
    Line_Figure copy = {start_copy, end_copy};
    return copy;
}

Point_Figure getCentroidLine(Line_Figure line) {
    Point_Figure centroid;

    centroid.x = (line.start.x + line.end.x) / 2;
    centroid.y = (line.start.y + line.end.y) / 2;

    return centroid;
}

void scale_line(Line_Figure *line, Point_Figure factor) {
    Point_Figure center = getCentroidLine(*line);
    Point_Figure foward = {-center.x, -center.y};

    float * Tfoward = getTranslateMatrix(foward);
    float * scale = getScaleMatrix(factor);
    float * Treturn = getTranslateMatrix(center);

    multiplyMatrix2D(Treturn, scale);
    multiplyMatrix2D(Treturn, Tfoward);

    multiplyByPointMatrix2D(Treturn, &line->start);
    multiplyByPointMatrix2D(Treturn, &line->end);

    free(Tfoward);
    Tfoward = NULL;

    free(scale);
    scale = NULL;

    free(Treturn);
    Treturn = NULL;
}

void rotate_line(Line_Figure *line, float angle) {
    Point_Figure center = getCentroidLine(*line);
    Point_Figure foward = {-center.x, -center.y};

    float * Tfoward = getTranslateMatrix(foward);
    float * rotate = getRotateMatrix(angle);
    float * Treturn = getTranslateMatrix(center);

    multiplyMatrix2D(Treturn, rotate);
    multiplyMatrix2D(Treturn, Tfoward);

    multiplyByPointMatrix2D(Treturn, &line->start);
    multiplyByPointMatrix2D(Treturn, &line->end);

    free(Tfoward);
    Tfoward = NULL;

    free(rotate);
    rotate = NULL;

    free(Treturn);
    Treturn = NULL;
}

void translate_line(Line_Figure *line, Point_Figure offset) {
    float * foward = getTranslateMatrix(offset);

    multiplyByPointMatrix2D(foward, &line->start);
    multiplyByPointMatrix2D(foward, &line->end);

    free(foward);
    foward = NULL;
}

LineList *newLineList() {
    LineList *list = (LineList *) malloc(sizeof(LineList *));

    if(*list != NULL)
        *list = NULL;

    return list;
}

LineList *copyLineList(LineList *list) {

    Line_Figure aux;
    LineList *copy = newLineList();

    for(int i = 0; i < lengthLineList(list); i++) {
        getLineList(list, i, &aux);
        addLineList(copy, aux);
    }

    return copy;
}

void clearLineList(LineList* list) {
    if(!isEmptyLineList(list)) {
        LineLink *current= *list, *aux = NULL;

        while(current != NULL) {
            aux = current;
            current = current->next;
            free(aux);
            aux = NULL;
        }
    }

    *list = NULL;
}

void deleteLineList(LineList *list) {
    clearLineList(list);
    free(list);
    list = NULL;
}

int isEmptyLineList(LineList *list) {
    if(*list == NULL) return 1;
    return 0;
}

int isNullLineList(LineList *list) {
    if(list == NULL) return 1;
    return 0;
}

int isNullOrEmptyLineList(LineList *list) {
    return isEmptyLineList(list) || isNullLineList(list);
}

void addToInitLineList(LineList *list, Line_Figure line) {
    LineLink *node = (LineLink *) malloc(sizeof(LineLink));
    node->line = line;
    node->next = *list;
    *list = node;
}

void addToEndLineList(LineList *list, Line_Figure line) {
    LineLink *node = (LineLink *) malloc(sizeof(LineLink));
    node->line = line;
    node->next = NULL;

    LineLink *aux = *list;

    while(aux->next != NULL) {
        aux = aux->next;
    }

    aux->next = node;
}

int addLineList(LineList *list, Line_Figure line) {
    if(list == NULL) return -1;

    if(isEmptyLineList(list))
        addToInitLineList(list, get_line_copy(line));
    else
        addToEndLineList(list, get_line_copy(line));

    return 1;
}

int fixIndexLineList(LineList *list, int index) {
    int rest, term, negative = -index, length = lengthLineList(list);

    if(index < 0) {
        rest = index % length;
        term = negative == length ? 0 : length;

        index = rest == 0 ? 0 : rest + term;
    }

    return index;
}

int reverseIndexLineList(LineList *list, int index) {
    if(index > 0)
        return fixIndexLineList(list, -index);
    else
        return fixIndexLineList(list, index);
}

void removeToInitLineList(LineList *list) {
    LineLink *aux = *list;
    *list = aux->next;
    free(aux);
    aux = NULL;
}

void removeToMiddleLineList(LineList *list, int index) {
    LineLink *current = *list, *prev = NULL;

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

int removeLineList(LineList *list, int index) {
    if(isNullOrEmptyLineList(list)) return -1;
    if(index > lengthLineList(list) || index < 0) return -1;

    if(index == 0)
        removeToInitLineList(list);
    else
        removeToMiddleLineList(list, index);

    return 1;
}

int lengthLineList(LineList *list) {
    if(isNullOrEmptyLineList(list)) return 0;

    int length = 0;
    LineLink *aux = *list;

    while(aux != NULL) {
        aux = aux->next;
        length++;
    }

    return length;
}

void copyDataLineList(LineList *list, int index, Line_Figure* copy) {

    LineLink *current = *list;

    for(int i = 0; i < index && current != NULL; i++)
        current = current->next;

    if(current != NULL) {
        *copy = current->line;
    }
}

int getLineList(LineList *list, int index, Line_Figure *copy) {
    if(isNullOrEmptyLineList(list)) return -1;
    if(index > lengthLineList(list) || index < 0) return -1;

    copyDataLineList(list, index, copy);
    return 1;
}

int updateLineList(LineList *list, int index, Line_Figure line) {
    if(isNullOrEmptyLineList(list)) return -1;
    if(index > lengthLineList(list) || index < 0) return -1;

    LineLink *current = *list;

    for(int i = 0; i < index && current != NULL; i++)
        current = current->next;

    if(current != NULL) {
        current->line = line;
    }

    return 1;
}

int indexOfLineList(LineList *list, Line_Figure line) {
    if(isNullOrEmptyLineList(list)) return -1;

    int i = 0;
    LineLink *aux = *list;
    while(aux != NULL && !isLinesEquals(line, aux->line)) {
        aux = aux->next;
        i++;
    }

    if(aux != NULL)
        return i;

    return -1;
}

void foreachLineList(LineList *list, LineCallback func) {
    if(!isNullLineList(list)) {
        LineLink *aux = *list;

        while(aux != NULL) {
            func(aux->line);
            aux = aux->next;
        }
    }
}
