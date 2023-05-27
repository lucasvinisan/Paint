#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <GL/glut.h>
#include "design.h"

#define WINDOW_WIDTH 800.0
#define WINDOW_HEIGTH 600.0
#define WINDOW_DEPTH 600.0
#define WINDOW_POSITION_X 200.0
#define WINDOW_POSITION_Y 100.0


void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //Definindo uma cor de fundo
    glEnable(GL_DEPTH_TEST); //Habilitando o teste de profundidad
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGTH, WINDOW_HEIGTH, -WINDOW_DEPTH, WINDOW_DEPTH);

    lighting();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Limpar o buffer

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();


    //Definindo a posição da câmera

    gluLookAt(100, 200, 80, //Posição da câmera
              0, 0, 0, //Para onde  a câmera aponta
              0, 1, 0);


    glPushMatrix();
    design_Teapot();
    glPopMatrix();


    glPushMatrix();
    design_Sphere();
    glPopMatrix();

    glPushMatrix();
    design_toros();
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

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
