#include <windows.h>
#include <GL/glut.h>
#include <locale.h>
#include "function.h"


void init(void)
{
    glClearColor(1.0, 1.0, 1.0, 0.0); //cor da tela

    glMatrixMode(GL_PROJECTION); //matriz de posi��o
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); //proje��o ortogonal

}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT); //desenha o fundo e limpa a janela

    designPoint();
    designLine();
    designPoligon();

    glutSwapBuffers();


}


int main(int argc, char** argv)
{
    setlocale(LC_ALL, "Portuguese");
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(200, 0);
    glutCreateWindow("Paint");
    glutMouseFunc(mouse);
    createMenu();

    init();
    glutDisplayFunc(display);
    glutMainLoop();


    return 0;
}
