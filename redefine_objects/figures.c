#include <GL/glut.h>

void create_Teapot()
{
    glTranslatef(-200, 2, 100);
    glColor3f(0, 1, 1);
    glutSolidTeapot(40); //Tamanho do bule que aparecer� na tela
}

void create_Sphere()
{
    glTranslatef(50, 10, 100);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(40, 100, 10);
}

void create_Torus()
{
    glTranslatef(-50, -15, -60);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidTorus(15, 40, 100, 100);
}
