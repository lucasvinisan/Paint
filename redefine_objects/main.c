#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include "design.h"
#include "figures.h"

#define WINDOW_WIDTH 800.0
#define WINDOW_HEIGTH 600.0
#define WINDOW_DEPTH 600.0
#define WINDOW_POSITION_X 200.0
#define WINDOW_POSITION_Y 100.0


void init()
{
    glClearColor(0.128f, 0.128f, 0.128f, 0.0f);
    glEnable(GL_DEPTH_TEST); //Habilitando o teste de profundidade
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGTH, WINDOW_HEIGTH, -WINDOW_DEPTH, WINDOW_DEPTH);

    set_camera(-1.5, 1.0, 2.0);

    lighting();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Limpar o buffer

    glPushMatrix();
    design_wall();
    glPopMatrix();

    glutSwapBuffers();

}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
    glutCreateWindow("1° questão");
    CreateMenu();

    init();
    glutDisplayFunc(display);
    create_menu();
    glutMainLoop();
    return 0;
}
