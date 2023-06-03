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
    glClearColor(0.128f, 0.128f, 0.128f, 0.0f); //Definindo uma cor de fundo
    glEnable(GL_DEPTH_TEST); //Habilitando o teste de profundidad
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGTH, WINDOW_HEIGTH, -WINDOW_DEPTH, WINDOW_DEPTH);

    //set_camera(-1.0, 1.0, 1.0);

    /*Definindo a camerá perpectiva*/
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, WINDOW_WIDTH / WINDOW_HEIGTH, 0.1, 1200.0);
    set_camera(-200.0, 100.0, -100.0);
    glEnable(GL_COLOR_MATERIAL);
    lighting();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Limpar o buffer
    //Definindo a posição da câmera


    glPushMatrix();
    design_wall();
    glPopMatrix();

    glPushMatrix();
    properties_Toros();
    create_Torus();
    glPopMatrix();

    glPushMatrix();
    properties_Teapot();
    create_Teapot();
    glPopMatrix();

    glPushMatrix();
    properties_Sphere();
    create_Sphere();
    glPopMatrix();

    glPushMatrix();
    create_cone();
    properties_Cone();
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
    glutMainLoop();
    return 0;
}
