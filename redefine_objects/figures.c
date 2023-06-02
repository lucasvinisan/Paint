#include <GL/glut.h>

void create_Teapot()
{
    glTranslatef(-200, 90, 100);
    glColor3f(0, 1, 1);
    glutSolidTeapot(100);
}

void create_Sphere()
{
    glTranslatef(200, 110, 100);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(100, 100, 50);
}

void create_Torus()
{
    glTranslatef(10, 34, -200);
    glRotatef(90, 1, 0, 0);
    glColor3f(0.0, 1.0, 0.0);
    glutSolidTorus(25.0f, 100.0f, 50, 50);
}

void properties_Sphere()
{
    float diffuse[4] = {0.8f, 0.66f, 0.0f, 1.0f};
    float specular[4] = {0.8f, 0.9f, 0.8f, 1.0f};
    float shininess = 120.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


void properties_Toros()
{
    float diffuse[4] = {1.0f, 0.2f, 0.2f, 1.0f};
    float specular[4] = {0.9f, 1.0f, 0.8f, 1.0f};
    float shininess = 90.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}

void properties_Teapot()
{
    float diffuse[4] = {0.2f, 1.0f, 1.0f, 1.0f};
    float specular[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float shininess = 90.0f;

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


