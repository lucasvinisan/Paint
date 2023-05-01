#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h>

#include "buffer.h"
#include "function.h"

Buffer buffer;
int buffer_initialized = 0;

void buffer_init() {
    if(!buffer_initialized) {
        buffer_initialized = 1;
        buffer.mode = 1;
        buffer.select_toggle = 0;
        buffer.is_next_line = 1;
        buffer.is_next_polygon = 1;

        buffer.mouse_down_position.x = 0;
        buffer.mouse_down_position.y = 0;

        buffer.mouse_up_position.x = 0;
        buffer.mouse_up_position.y = 0;

        buffer.points_buffer = newPointList();

        buffer.lines_buffer = newLineList();
        buffer.lines_temp_buffer = newPointList();

        buffer.polygons_buffer = newPolygonList();
        buffer.polygons_temp_buffer = newPointList();
    }
}

Buffer get_buffer() {
    return buffer;
}

void buffer_set_mode(int mode) {
    buffer.mode = mode;
}

int buffer_get_mode(int mode) {
    return buffer.mode;
}

void buffer_set_mouse_down(float x, float y) {
    buffer.mouse_down_position.x = x;
    buffer.mouse_down_position.y = y;
}

Point_Figure buffer_get_mouse_down() {
    return buffer.mouse_down_position;
}

void buffer_set_mouse_up(float x, float y) {
    buffer.mouse_up_position.x = x;
    buffer.mouse_up_position.y = y;
}

Point_Figure buffer_get_mouse_up() {
    return buffer.mouse_up_position;
}

void buffer_add_point(float x, float y) {
    Point_Figure point = {x, y};
    printf("Point (%.2f, %.2f) added to points buffer\n", x, y);
    addPointList(buffer.points_buffer, point);
}

void buffer_clear_line_temp() {
    clearPointList(buffer.lines_temp_buffer);
}

void buffer_add_line_temp(Point_Figure point) {
    if(lengthPointList(buffer.lines_temp_buffer) == 1) {
        Point_Figure start;

        getPointList(buffer.lines_temp_buffer, 0, &start);
        buffer_add_line(start, point);

        buffer_clear_line_temp();
    }

    else {
//        printf("Point (%.2f, %.2f) added to lines temp buffer\n", point.x, point.y);
        addPointList(buffer.lines_temp_buffer, point);
    }
}

void buffer_add_line(Point_Figure start, Point_Figure end) {
    Line_Figure line = {start, end};
    printf("Line [(%.2f, %.2f), (%.2f, %.2f)] added to lines buffer\n",
    start.x, start.y, end.x, end.y);
    addLineList(buffer.lines_buffer, line);
}

void buffer_clear_polygon_temp() {
    clearPointList(buffer.polygons_temp_buffer);
}

void buffer_add_polygon(PointList vertex_list) {
    Polygon_Figure polygon = {vertex_list};
    addPolygonList(buffer.polygons_buffer, polygon);
}

void buffer_draw_points() {
    glPointSize(10.0);

    Point_Figure point;

    glBegin(GL_POINTS);
        glColor3f(1.0, 0.0, 0.0);
        for (int i = 0; i < lengthPointList(buffer.points_buffer); i++)
        {
            getPointList(buffer.points_buffer, i, &point);
            glVertex2f(point.x, point.y);
        }
    glEnd();
}
void buffer_draw_lines() {

    glLineWidth(2.0);

    Line_Figure line;

    glBegin(GL_LINES);
        glColor3f(0.0, 1.0, 0.0);
        for (int i = 0; i < lengthLineList(buffer.lines_buffer); i++)
        {
            getLineList(buffer.lines_buffer, i, &line);

            glVertex2f(line.start.x, line.start.y);
            glVertex2f(line.end.x, line.end.y);
        }
    glEnd();
}

void buffer_draw_polygons() {
    Polygon_Figure polygon;
    Point_Figure point;

    glBegin(GL_POLYGON);
        glColor3f(0.0, 0.0, 1.0);
        for (int i = 0; i < lengthPolygonList(buffer.polygons_buffer); i++)
        {
            getPolygonList(buffer.polygons_buffer, i, &polygon);
            for(int j = 0; j < lengthPointList(polygon.vertex_list); j++)
            {
                getPointList(polygon.vertex_list, j, &point);
                glVertex2f(point.x, point.y);
            }
        }
    glEnd();
}

void buffer_draw_all() {
    buffer_draw_polygons();
    buffer_draw_points();
    buffer_draw_lines();
}
