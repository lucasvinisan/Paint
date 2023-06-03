#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>

#define WINDOW_WIDTH 800.0
#define WINDOW_HEIGTH 600.0
#define WINDOW_DEPTH 600.0
#define WINDOW_POSITION_X 550.0
#define WINDOW_POSITION_Y 0.0

int rotate = 1;
int zoom = 100;
double angle = 0;
float zoom_factor = 1.0;
int viewport_width = round(WINDOW_WIDTH / 2);
int viewport_heigth = round(WINDOW_HEIGTH / 2);
void * default_font = GLUT_BITMAP_HELVETICA_18;

void init() {
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
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

void Text2D(char *text, int length, int x, int y, int z) {
    glRasterPos3f(x, y, z);

    glPushMatrix();
        for(int i = 0; i < length; i++) {
            glutBitmapCharacter(default_font, text[i]);
        }
    glPopMatrix();
}

void animation(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, animation, 0);

    angle += 0.005;

    if(angle >= 360) angle = 0;

    glPushMatrix();
        if(rotate) glRotatef(angle, 0, 1, 0);

        glutSolidTeapot(250.f);
    glPopMatrix();
}

void select_menu(int option) {
    switch(option) {
        case 0:
            rotate = !rotate;
            angle = 0;
            glLoadIdentity();
            break;

        case 1:
            zoom += 10;
            zoom_factor = zoom / 100.0;
            break;

        case 2:
            zoom -= 10;
            zoom_factor = zoom / 100.0;
            break;

        case 3:
            break;

        case 4:
            exit(0);

        default:
            break;
    }
    glutPostRedisplay();
}

void create_menu() {
    int menu = glutCreateMenu(select_menu);

    glutAddMenuEntry("Toggle Animation", 0);
    glutAddMenuEntry("Zoom in", 1);
    glutAddMenuEntry("Zoom out", 2);
    glutAddMenuEntry("Export image", 3);
    glutAddMenuEntry("Exit", 4);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouse(int button, int state, int x, int y) {

    switch(button) {
        case GLUT_RIGHT_BUTTON:
            break;

        case GLUT_MIDDLE_BUTTON:
            break;

        case GLUT_LEFT_BUTTON:
            break;

        default:
            break;
    }
}

void render_border_box(float start_x, float start_y, float end_x, float end_y, int width) {
    glLineWidth(width);

    glBegin(GL_LINE_STRIP);
        glVertex3f(start_x, start_y, -WINDOW_DEPTH);
        glVertex3f(end_x, start_y, -WINDOW_DEPTH);
        glVertex3f(end_x, end_y, -WINDOW_DEPTH);
        glVertex3f(start_x, end_y, -WINDOW_DEPTH);
    glEnd();
}

void display() {
    char status [51];

    snprintf(status, 51, "Zoom %d%%                       Animation %s", zoom, rotate? "enabled" : "disabled");

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, viewport_heigth, viewport_width, viewport_heigth);
        gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
        animation(0);
        glLoadIdentity();

        render_border_box(-WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_WIDTH, -WINDOW_HEIGTH, 2);
        Text2D(status, 51, -WINDOW_WIDTH + 50, WINDOW_HEIGTH - 100, -WINDOW_DEPTH);
        Text2D("XY", 2, WINDOW_WIDTH - 200, -WINDOW_HEIGTH + 50, -WINDOW_DEPTH);

    glViewport(viewport_width, viewport_heigth, viewport_width, viewport_heigth);
        gluLookAt(-10, 0, 0, 0, 0, 0, 0, 1, 0);
        animation(0);
        glLoadIdentity();

        render_border_box(-WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_WIDTH, -WINDOW_HEIGTH, 2);
        Text2D("YZ", 2, WINDOW_WIDTH - 200, -WINDOW_HEIGTH + 50, -WINDOW_DEPTH);

    glViewport(0, 0, viewport_width, viewport_heigth);
        gluLookAt(0, -10, 0, 0, 0, 0, 0, 0, 1);
        animation(0);
        glLoadIdentity();

        render_border_box(-WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_WIDTH, -WINDOW_HEIGTH, 2);
        Text2D("XZ", 2, WINDOW_WIDTH - 200, -WINDOW_HEIGTH + 50, -WINDOW_DEPTH);

    glViewport(viewport_width, 0, viewport_width, viewport_heigth);
        gluLookAt(-50, -100, 200, 0, 0, 0, 0, 1, 0);
        gluPerspective(10, 0.5, 300, 300);
        animation(0);
        glLoadIdentity();

        render_border_box(-WINDOW_WIDTH, WINDOW_HEIGTH, WINDOW_WIDTH, -WINDOW_HEIGTH, 2);
        Text2D("Perspectiva", 11, WINDOW_WIDTH - 500, -WINDOW_HEIGTH + 50, -WINDOW_DEPTH);

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGTH);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutCreateWindow("Teapot 3D by L&K");

    init();

    create_menu();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutTimerFunc(0, animation, 0);
    glutMainLoop();

    return 0;
}
