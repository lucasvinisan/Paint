#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>

#define WINDOW_WIDTH 800.0
#define WINDOW_HEIGTH 600.0
#define WINDOW_DEPTH 600.0
#define WINDOW_POSITION_X 550.0
#define WINDOW_POSITION_Y 0.0

void init() {
    glClearColor(0, 0, 0, 0);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGTH, WINDOW_HEIGTH, WINDOW_DEPTH, -WINDOW_DEPTH);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);

    float global_light[] = {.2f, .2f, .2f, .2f};

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_light);

    float sun[4][4] = {
        {0.1f, 0.1f, 0.1f, 1.0f},
        {0.8f, 0.8f, 0.8f, 1.0f},
        {1.0f, 1.0f, 1.0f, 1.0f},
        {100.0f, 110.0f, -110.0f, 1.0f}
    };

    glLightfv(GL_LIGHT0, GL_AMBIENT, &sun[0][0]);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, &sun[1][0]);
    glLightfv(GL_LIGHT0, GL_SPECULAR, &sun[2][0]);
    glLightfv(GL_LIGHT0, GL_POSITION, &sun[3][0]);

    glEnable(GL_LIGHT0);

//    glLoadIdentity();
//    gluLookAt(-50, -100, 200, 0, 0, 0, 0, 1, 0);
//    glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
    glColor3f(.1f, .5f, 1.f);
    gluLookAt(-50, -100, 200, 0, 0, 0, 0, 1, 0);
    glutSolidTeapot(100.f);

//    glLoadIdentity();
//    glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
//    gluLookAt(-50, -100, 200, 0, 0, 0, 0, 1, 0);
//    glColor3f(.5f, .5f, 1.f);
//    glutSolidTeapot(100.f);
//
//        glLoadIdentity();
//    gluLookAt(-50, -100, 200, 0, 0, 0, 0, 1, 0);
//    glViewport(0, WINDOW_HEIGTH / 2, WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
//    glColor3f(.5f, .1f, .1f);
//    glutSolidTeapot(100.f);
//
//    glLoadIdentity();
//    glViewport(WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2, WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
//    gluLookAt(-50, -100, 200, 0, 0, 0, 0, 1, 0);
//    glColor3f(.5f, .0f, 1.f);
//    glutSolidTeapot(100.f);

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutCreateWindow("Teapot 3D by L&K");

    init();

    glutDisplayFunc(display);
    glutMainLoop();


    return 0;
}
