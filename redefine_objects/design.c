#include <GL/glut.h>
#include "figures.h"

#define WINDOW_WIDTH 800.0
#define WINDOW_HEIGTH 600.0
#define WINDOW_DEPTH 600.0
#define WINDOW_POSITION_X 200.0
#define WINDOW_POSITION_Y 100.0

#define positionx -1.0
#define positiony 1.0
#define positionz 1.0

typedef struct scenery{
    float translate_position_x, translate_position_y, translate_position_z;
    float rotate_position_x, rotate_position_y, rotate_position_z, rotate_angle;
    float scale_position_x, scale_posistion_y, scale_posistion_z;
    float size;
}Scenary;


void design_wall()
{
    Scenary scenery[3];
    properties();

    scenery[0].size = 200.0;
    scenery[1].size = 200.0;
    scenery[2].size = 200.0;

    /*Parede em x*/

    scenery[0].scale_position_x  = 5.1;
    scenery[0].scale_posistion_y = 1.0;
    scenery[0].scale_posistion_z = 0.1;


    scenery[0].translate_position_x = 0.0;
    scenery[0].translate_position_y = 90.0;
    scenery[0].translate_position_z = -400.0;

    /*Parede em z*/

    scenery[1].scale_position_x  = 0.1;
    scenery[1].scale_posistion_y = 1.0;
    scenery[1].scale_posistion_z = 4.0;

    scenery[1].translate_position_x = 500.0;
    scenery[1].translate_position_y = 90.0;
    scenery[1].translate_position_z = 0.0;

    /*Chao*/
    scenery[2].scale_position_x  = 5.1;
    scenery[2].scale_posistion_y = 0.1;
    scenery[2].scale_posistion_z = 4.0;



    glPushMatrix();
    glTranslatef(scenery[0].translate_position_x, scenery[0].translate_position_y, scenery[0].translate_position_z);
    //glRotatef(scenery[0].rotate_angle, scenery[0].rotate_position_x, scenery[0].rotate_position_y, scenery[0].rotate_position_z);sca
    glScalef(scenery[0].scale_position_x, scenery[0].scale_posistion_y, scenery[0].scale_posistion_z);
    glColor3f(1.0f, 0.0, 0.0);
    glutSolidCube(scenery[0].size);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(scenery[1].translate_position_x, scenery[1].translate_position_y, scenery[1].translate_position_z);
    //glRotatef(scenery[1].rotate_angle, scenery[1].rotate_position_x, scenery[1].rotate_position_y, scenery[1].rotate_position_z);
    glScalef(scenery[1].scale_position_x, scenery[1].scale_posistion_y, scenery[1].scale_posistion_z);
    glColor3f(1.0f, 0.0, 0.0);
    glutSolidCube(scenery[1].size);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0, 0.0);
    glScalef(scenery[2].scale_position_x, scenery[2].scale_posistion_y, scenery[2].scale_posistion_z);
    glutSolidCube(scenery[2].size);
    glPopMatrix();


    glPushMatrix();
    create_Torus();
    glPopMatrix();

    glPushMatrix();
    create_Teapot();
    glPopMatrix();

    glPushMatrix();
    create_Sphere();
    glPopMatrix();

    glPushMatrix();
    create_cone();
    glPopMatrix();

}

void lighting()
{
    GLfloat position[4] = {-0.2f, 0.1f, 0.0f, 0.0f}; //Posição da camêra
    GLfloat white[4]    = {1.0f, 1.0f, 1.0f, 1.0f}; //ùltimo elemento ó ahpa
    GLfloat black[4]    = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    //Ativando iluminação
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


void set_camera(float position_x, float position_y, float position_z)
{
    gluLookAt(position_x, position_y, position_z, //Posição da câmera
              0, 0, 0, //Para onde  a câmera aponta
              0, 1, 0);
}

void set_camera_ambiente()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-WINDOW_WIDTH, WINDOW_WIDTH, -WINDOW_HEIGTH, WINDOW_HEIGTH, -WINDOW_DEPTH, WINDOW_DEPTH);
    set_camera(-1.0, 1.0, 1.0);
}

void set_camera_perpective()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(120.0, WINDOW_WIDTH / WINDOW_HEIGTH, 0.1, 1200.0);
    set_camera(-100.0, 100.0, 100.0);
}


void select_menu(int option) {
    switch(option) {
        case 0:
            set_camera_perpective();
            break;
        case 1:
            set_camera_ambiente(positionx, positiony, positionz);
            break;
        case 2:
            glEnable(GL_DEPTH_TEST);
            break;
        case 3:
            glDisable(GL_DEPTH_TEST);
            break;
        case 4:
            break;
        case 5:
            glEnable(GL_COLOR_MATERIAL);
            break;
        case 6:
            glDisable(GL_COLOR_MATERIAL);
            break;
        case 7:
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

void create_menu() {
    int menu = glutCreateMenu(select_menu);

    glutAddMenuEntry("Perspective camera", 0);
    glutAddMenuEntry("Camera", 1);
    glutAddMenuEntry("Enable depth test", 2);
    glutAddMenuEntry("Disable depth test", 3);
    glutAddMenuEntry("Move camera", 4);
    glutAddMenuEntry("Enable color material", 5);
    glutAddMenuEntry("Disable color material", 6);
    glutAddMenuEntry("Exit", 7);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

