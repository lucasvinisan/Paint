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
        buffer.mode = 0;
        buffer.select_index = 0;
        buffer.is_next_line = 0;

        buffer.mouse_down_position.x = 0;
        buffer.mouse_down_position.y = 0;

        buffer.mouse_up_position.x = 0;
        buffer.mouse_up_position.y = 0;

        buffer.points_buffer = newPointList();

        buffer.lines_buffer = newLineList();

        buffer.polygons_buffer = newPolygonList();
        buffer.polygons_temp_buffer = newPointList();
    }
}

Buffer *buffer_get() {
    return &buffer;
}

void buffer_set_mode(int mode) {

    if(!isEmptyPointList(buffer.polygons_temp_buffer)) {
        buffer_add_polygon(buffer.polygons_temp_buffer);
        buffer_clear_polygon_temp();
    }
    buffer.mode = mode;
}

int buffer_get_mode() {
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

void buffer_add_line_temp(Point_Figure point) {
    if(buffer.is_next_line) {
        buffer_add_line(buffer_get_mouse_down(), point);
        buffer.is_next_line = 0;
    }

    else {
         buffer.is_next_line = 1;
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

void buffer_add_polygon_temp() {
    Point_Figure point = buffer_get_mouse_down();
    addPointList(buffer.polygons_temp_buffer, point);
//    printf("Point (%.2f, %.2f) added to polygons temp buffer\n", point.x, point.y);
}

void buffer_add_polygon(PointList vertex_list) {
    Polygon_Figure polygon = {vertex_list};
    addPolygonList(buffer.polygons_buffer, polygon);
    printf("Polygon ");
    foreachPolygonList(buffer.polygons_buffer, print_polygon);
    printf(" added to polygons buffer\n");
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

void buffer_draw_temp_line() {
    if(buffer_get_mode() == 1)
    {
        Point_Figure point = buffer_get_mouse_down();

        glBegin(GL_POINTS);
            glColor3f(0, 1, 0.2);
            glVertex2f(point.x, point.y);
        glEnd();
    }
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

        glColor3f(0.0, 0.0, 1.0);
        for (int i = 0; i < lengthPolygonList(buffer.polygons_buffer); i++)
        {
            getPolygonList(buffer.polygons_buffer, i, &polygon);
            glBegin(GL_POLYGON);
                for(int j = 0; j < lengthPointList(polygon.vertex_list); j++)
                {
                    getPointList(polygon.vertex_list, j, &point);
                    glVertex2f(point.x, point.y);
                }
            glEnd();
        }
}

void buffer_draw_temp_polygon() {
    Point_Figure point;

    int length = lengthPointList(buffer.polygons_temp_buffer);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(0.0, 0.5, 1.0);

    if(length > 2) {
        glBegin(GL_POLYGON);
            for(int i = 0; i < length; i++) {
                getPointList(buffer.polygons_temp_buffer, i, &point);
                glVertex2f(point.x, point.y);
            }
        glEnd();
    }
    else if(length > 1) {
        glLineWidth(2.0);
        glBegin(GL_LINES);
            for(int i = 0; i < length; i++) {
                getPointList(buffer.polygons_temp_buffer, i, &point);
                glVertex2f(point.x, point.y);
            }
        glEnd();
    }
    else {
        glPointSize(10.0);
        glBegin(GL_POINTS);
            for(int i = 0; i < length; i++) {
                getPointList(buffer.polygons_temp_buffer, i, &point);
                glVertex2f(point.x, point.y);
            }
        glEnd();
    }
    glDisable(GL_BLEND);
}

void buffer_draw_all() {
    buffer_draw_temp_polygon();
    buffer_draw_polygons();
    buffer_draw_temp_line();
    buffer_draw_points();
    buffer_draw_lines();
}

void buffer_translate_point() {
    Point_Figure point;

    if(getPointList(buffer.points_buffer, buffer.select_index, &point) != -1) {

        translate_point(&point, buffer_get_mouse_down());
        updatePointList(buffer.points_buffer, buffer.select_index, point);
    }
}

void buffer_scale_line(Point_Figure factor) {
    Line_Figure line;

    if(getLineList(buffer.lines_buffer, buffer.select_index, &line) != -1) {
        scale_line(&line, factor);
        updateLineList(buffer.lines_buffer, buffer.select_index, line);
    }
}

void buffer_rotate_line(float angle) {
    Line_Figure line;

    if(getLineList(buffer.lines_buffer, buffer.select_index, &line) != -1) {
        rotate_line(&line, angle);
        updateLineList(buffer.lines_buffer, buffer.select_index, line);
    }
}

void buffer_translate_line() {
    Line_Figure line;

    if(getLineList(buffer.lines_buffer, buffer.select_index, &line) != -1) {
        translate_line(&line, buffer_get_mouse_down());
        updateLineList(buffer.lines_buffer, buffer.select_index, line);
    }
}

void buffer_scale_polygon(Point_Figure factor) {
    Polygon_Figure polygon;

    if(getPolygonList(buffer.polygons_buffer, buffer.select_index, &polygon) != -1) {
        scale_polygon(&polygon, factor);
        updatePolygonList(buffer.polygons_buffer, buffer.select_index, polygon);
    }
}

void buffer_rotate_polygon(float angle) {
    Polygon_Figure polygon;

    if(getPolygonList(buffer.polygons_buffer, buffer.select_index, &polygon) != -1) {
        rotate_polygon(&polygon, angle);
        updatePolygonList(buffer.polygons_buffer, buffer.select_index, polygon);
    }
}

void buffer_translate_polygon() {
    Polygon_Figure polygon;

    if(getPolygonList(buffer.polygons_buffer, buffer.select_index, &polygon) != -1) {
        translate_polygon(&polygon, buffer_get_mouse_down());
        updatePolygonList(buffer.polygons_buffer, buffer.select_index, polygon);
    }
}

void buffer_remove_point() {
    removePointList(buffer.points_buffer, buffer.select_index);
}

void buffer_remove_line() {
    removeLineList(buffer.lines_buffer, buffer.select_index);
}

void buffer_remove_polygon() {
    removePolygonList(buffer.polygons_buffer, buffer.select_index);
}
