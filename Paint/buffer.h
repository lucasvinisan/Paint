#ifndef BUFFER_H_INCLUDED
#define BUFFER_H_INCLUDED

#include "point.h"
#include "line.h"
#include "polygon.h"
#include "function.h"

typedef struct {
    int mode;
    int select_toggle;
    int is_next_line;
    int is_next_polygon;

    Point_Figure mouse_down_position;
    Point_Figure mouse_up_position;

    PointList *points_buffer;

    LineList *lines_buffer;

    PolygonList *polygons_buffer;
    PointList *polygons_temp_buffer;
} Buffer;

void buffer_init();

Buffer get_buffer();

void buffer_set_mode(int mode);

int buffer_get_mode();

void buffer_set_mouse_down(float x, float y);

Point_Figure buffer_get_mouse_down();

void buffer_set_mouse_up(float x, float y);

Point_Figure buffer_get_mouse_up();

void buffer_add_point(float x, float y);

void buffer_add_line_temp(Point_Figure point);

void buffer_clear_line_temp();

void buffer_add_line(Point_Figure start, Point_Figure end);

void buffer_add_polygon_temp(Point_Figure point);

void buffer_clear_polygon_temp();

void buffer_add_polygon(PointList vertex_list);

void buffer_draw_points();

void buffer_draw_lines();

void buffer_draw_polygons();

void buffer_draw_all();

#endif // BUFFER_H_INCLUDED
