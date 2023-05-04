#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <gl/glut.h>

#include "buffer.h"
#include "transform.h"

#define WINDOW_WIDTH 600.0
#define WINDOW_HEIGTH 600.0
#define WINDOW_POSITION_X 650.0
#define WINDOW_POSITION_Y 0.0

void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, WINDOW_WIDTH, WINDOW_HEIGTH, 0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    buffer_init();
    buffer_draw_all();

    glutSwapBuffers();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutCreateWindow("Paint by L&K");
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(keyboardSpecial);
    create_menu();

    init();
    glutDisplayFunc(display);
    glutMainLoop();

    return 0;
}
