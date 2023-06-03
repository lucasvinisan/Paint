#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>

#define WINDOW_WIDTH 800.0
#define WINDOW_HEIGTH 600.0
#define WINDOW_DEPTH 600.0
#define WINDOW_POSITION_X 550.0
#define WINDOW_POSITION_Y 0.0

double angle = 0;
int rotate = 1;

void init() {
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glClearColor(.5, .5, .5, .5);
    glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGTH, WINDOW_HEIGTH, WINDOW_DEPTH, -WINDOW_DEPTH);
    lighting();
}

void lighting() {
    float global_light[3] = {.2f, .2f, .2f};
    float ligth0_position[] = {0, 175, -1000, 1};
    float ligth0_ambient[] = {0, 0, 0, 1};
    float ligth0_diffuse[] = {1, 1, 1, 1};
    float ligth0_specular[] = {1, 1, 1, 1};

    float material_diffuse[] = {1.f, .5f, 0.f, 1};
    float material_specular[] = {.9f, .9f, .9f, 1};
    float material_shininess = 70;

    glLightfv(GL_LIGHT0, GL_POSITION, ligth0_position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ligth0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, ligth0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, ligth0_specular);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_light);

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, material_shininess);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void Text2D(char *text, int length, int font, int x, int y) {

}

void animation(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, animation, 0);

    angle += 0.005;

    if(angle >= 360) angle = 0;

    glPushMatrix();
        if(rotate) glRotatef(angle, 0, 1, 0.1);

        else {

        }

        glutSolidTeapot(250.f);
    glPopMatrix();
}

void mouse(int button, int state, int x, int y) {

    switch(button) {
        case GLUT_MIDDLE_BUTTON:
            if(state == GLUT_DOWN)
                rotate = !rotate;

            angle = 0;
            glLoadIdentity();
            break;

        default:
            break;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, WINDOW_HEIGTH / 2, WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
    animation(0);
    glLoadIdentity();
    glViewport(WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2, WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
    gluLookAt(-10, 0, 0, 0, 0, 0, 0, 1, 0);
    animation(0);
    glLoadIdentity();

    glViewport(0, 0, WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
    gluLookAt(0, -10, 0, 0, 0, 0, 0, 0, 1);
    animation(0);
    glLoadIdentity();
    glViewport(WINDOW_WIDTH / 2, 0, WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
    gluLookAt(-50, -100, 200, 0, 0, 0, 0, 1, 0);
    gluPerspective(10, 0.5, 300, 300);
    animation(0);
    glLoadIdentity();

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
    glutMouseFunc(mouse);
    glutTimerFunc(0, animation, 0);
    glutMainLoop();

    return 0;
}
