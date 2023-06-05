#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <gl/glut.h>

#define WINDOW_WIDTH 800.0
#define WINDOW_HEIGHT 600.0
#define WINDOW_DEPTH 600.0
#define WINDOW_POSITION_X 550.0
#define WINDOW_POSITION_Y 0.0

int toggle_rotation = 1;
int toggle_texture = 0;
double angle = 0;
int viewport_width = round(WINDOW_WIDTH / 2);
int viewport_heigth = round(WINDOW_HEIGHT / 2);
void * default_font = GLUT_BITMAP_HELVETICA_18;

GLuint texture;
int texture_width = 256;
int texture_height = 256;
char texture_path[] = "teapot_texture_1.bmp";

int zoom = 100;
float zm_factor = 1.0;
float zm_width = WINDOW_WIDTH, zm_height = WINDOW_HEIGHT, zm_depth = WINDOW_DEPTH;

void init() {
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    glMatrixMode(GL_PROJECTION);
    glClearColor(.5f, .5f, .5f, 1);
    glOrtho(-zm_width, zm_width, -zm_height, zm_height, zm_depth, -zm_depth);
    lighting();
}

void lighting() {
    float global_light[3] = {.2f, .2f, .2f};
    float ligth0_position[] = {1000, 1000, -1000, 1};
    float ligth0_ambient[] = {0, 0, 0, 1};
    float ligth0_diffuse[] = {1, 1, 1, 1};
    float ligth0_specular[] = {1, 1, 1, 1};

    float material_diffuse[] = {1.f, .5f, 0.f, 1};
    float material_specular[] = {.9f, .9f, .9f, 1};
    float material_shininess = 0.5;

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
    glutTimerFunc(16, animation, 0);

    angle += 0.005;

    if(angle >= 360) angle = 0;

    glPushMatrix();
        if(toggle_rotation) glRotatef(angle, 0, 1, 0);

        glutSolidTeapot(250.f * zm_factor);
    glPopMatrix();
    glutPostRedisplay();
}

void export_image(char * filename, short img_width, short img_height) {
    int img_size = 3 * img_width * img_height;
    FILE *img_file = fopen(filename, "w");

    char data[img_size];
    short tga_head[] = {0, 0, 0, 0, 0, 0, img_width, img_height, 24};

    glReadBuffer(GL_FRONT);
    glReadPixels(0, 0, img_width, img_height, 0x80E0, GL_UNSIGNED_BYTE, data);
    fwrite(&tga_head, sizeof(tga_head), 1, img_file);
    fwrite(data, img_size, 1, img_file);
    fclose(img_file);

    printf("%s was created\n", filename);
}

void select_menu(int option) {
    switch(option) {
        case 0:
            zoom += (zoom >= 200) ? 0 : 10;
            zm_factor = zoom / 100.0;
            break;

        case 1:
            zoom -= (zoom <= 10) ? 0 : 10;
            zm_factor = zoom / 100.0;
            glOrtho(-zm_width, zm_width, -zm_height, zm_height, zm_depth, -zm_depth * zoom);
            break;

        case 2:
            zoom = 100;
            zm_factor = zoom / 100.0;
            break;

        case 3:
            toggle_rotation = !toggle_rotation;
            angle = 0;
            break;

        case 4:
            toggle_texture = !toggle_texture;
            break;

        case 5:
            export_image("teapot_3d_image", WINDOW_WIDTH, WINDOW_HEIGHT);
            break;

        case 6:
            exit(0);

        default:
            break;
    }
    glutPostRedisplay();
}

void create_menu() {
    int menu = glutCreateMenu(select_menu);

    glutAddMenuEntry("Zoom in", 0);
    glutAddMenuEntry("Zoom out", 1);
    glutAddMenuEntry("Zoom reset", 2);
    glutAddMenuEntry("Toggle Animation", 3);
    glutAddMenuEntry("Toggle texture", 4);
    glutAddMenuEntry("Export image", 5);
    glutAddMenuEntry("Exit", 6);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
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

const char *bool_to_char(unsigned short int boolean) {
    return boolean? "enabled " : "disabled";
}

void display() {
    char zoom_status [10];
    char texture_status [20];
    char animation_status [20];

    snprintf(zoom_status, 10, "Zoom %d%%", zoom, bool_to_char(toggle_rotation), bool_to_char(toggle_texture));
    snprintf(animation_status, 20, "Animation %s", bool_to_char(toggle_rotation));
    snprintf(texture_status, 20, "Texture %s", bool_to_char(toggle_texture));

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glViewport(0, viewport_heigth, viewport_width, viewport_heigth);
        gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
        animation(0);
        glLoadIdentity();

        render_border_box(-zm_width, zm_height, zm_width, -zm_height, 2);
        Text2D(zoom_status, 10, -zm_width + 50, zm_height - 100, -WINDOW_DEPTH);
        Text2D(animation_status, 19, zm_width - 700, zm_height - 100, -WINDOW_DEPTH);
        Text2D("XY", 2, zm_width - 200, -zm_height + 50, -WINDOW_DEPTH);

    glViewport(viewport_width, viewport_heigth, viewport_width, viewport_heigth);
        gluLookAt(-10, 0, 0, 0, 0, 0, 0, 1, 0);
        animation(0);
        glLoadIdentity();

        Text2D(texture_status, 20, -zm_width + 50, zm_height - 100, -WINDOW_DEPTH);
        Text2D("YZ", 2, zm_width - 200, -zm_height + 50, -WINDOW_DEPTH);
        render_border_box(-zm_width, zm_height, zm_width, -zm_height, 2);

    glViewport(0, 0, viewport_width, viewport_heigth);
        gluLookAt(0, -10, 0, 0, 0, 0, 0, 0, 1);
        animation(0);
        glLoadIdentity();

        render_border_box(-zm_width, zm_height, zm_width, -zm_height, 2);
        Text2D("XZ", 2, zm_width - 200, -zm_height + 50, -WINDOW_DEPTH);

    glViewport(viewport_width, 0, viewport_width, viewport_heigth);
        gluLookAt(-50, -100, 200, 0, 0, 0, 0, 1, 0);
        gluPerspective(10, 0.5, 300, 300);
        animation(0);
        glLoadIdentity();

        render_border_box(-zm_width, zm_height, zm_width, -zm_height, 2);
        Text2D("Perspectiva", 11, zm_width - 500, -zm_height + 50, -WINDOW_DEPTH);

    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(zm_width, zm_height);
    glutInitWindowPosition(WINDOW_POSITION_X, WINDOW_POSITION_Y);
    glutCreateWindow("Teapot 3D by L&K");

    init();

    create_menu();
    glutDisplayFunc(display);
    glutTimerFunc(0, animation, 0);
    glutMainLoop();

    return 0;
}
