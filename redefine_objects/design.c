#include <GL/glut.h>


void design_Teapot()
{
    glTranslatef(-140, 20, 150);
    glColor3f(0, 1, 0);
    glutSolidTeapot(80.f); //Tamanho do bule que aparecerá na tela
}

void design_Sphere()
{
    glTranslatef(140, 20, -150);
    glColor3f(0, 0, 1);
    glutSolidSphere(80, 50, 10);
}

void design_toros()
{
    glTranslatef(300, 20, 150);
    glRotatef(90, 1, 0, 0); //Rotaciona 90 graus em torno do eixo x
    glColor3f(1, 0, 0);
    glutSolidTorus(30, 80, 50, 50);
}

void lighting()
{
    float position[4] = {500.0f, 400.0f, 0.0f, 1.0f};
    float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    float black[4] = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    //Ativando iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

}
