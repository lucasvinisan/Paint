#include <GL/glut.h>
#include "figures.h"


typedef struct scenery{
    float translate_position_x, translate_position_y, translate_position_z;
    float rotate_position_x, rotate_position_y, rotate_position_z, rotate_angle;
    float scale_position_x, scale_posistion_y, scale_posistion_z;
    float size;
    struct Figure* figure;
}Scenary;


void design_wall()
{
    Scenary scenery[3];
    Figure figure[10];

    scenery[0].size = 100.0;
    scenery[1].size = 100.0;
    scenery[2].size = 100.0;

    scenery[0].translate_position_x = -50.0;
    scenery[0].translate_position_y = 0.0;
    scenery[0].translate_position_z = -206.0;

    /*scenery[0].rotate_position_x = 0.0;
    scenery[0].rotate_position_y = 1.0;
    scenery[0].rotate_position_z = 0.0;
    scenery[0].rotate_angle = 40.0;*/

    scenery[0].scale_position_x  = 5.0;
    scenery[0].scale_posistion_y = 1.0;
    scenery[0].scale_posistion_z = 0.2;

    //glScalef(0.3, 2.0, 10.0);

    scenery[1].translate_position_x = 200.0;
    scenery[1].translate_position_y = 0.0;
    scenery[1].translate_position_z = -6.0;

    /*scenery[1].rotate_position_x = 1.0;
    scenery[1].rotate_position_y = 0.0;
    scenery[1].rotate_position_z = 0.0;
    scenery[1].rotate_angle = 40.0;*/

    scenery[1].scale_position_x  = 0.2;
    scenery[1].scale_posistion_y = 1.0;
    scenery[1].scale_posistion_z = 4.11;

    /*Ch�o*/
    scenery[2].translate_position_x = -50.0;
    scenery[2].translate_position_y = -40.0;
    scenery[2].translate_position_z = 0.0;

    scenery[2].scale_position_x  = 5.0;
    scenery[2].scale_posistion_y = 0.2;
    scenery[2].scale_posistion_z = 4.0;

    //glTranslatef(10, 20, 0);
    //glRotatef(90, 0, 1, 0);
    //glScalef(0.3, 2.0, 10.0);


    glPushMatrix();
    glTranslatef(scenery[0].translate_position_x, scenery[0].translate_position_y, scenery[0].translate_position_z);
    //glRotatef(scenery[0].rotate_angle, scenery[0].rotate_position_x, scenery[0].rotate_position_y, scenery[0].rotate_position_z);sca
    glScalef(scenery[0].scale_position_x, scenery[0].scale_posistion_y, scenery[0].scale_posistion_z);
    set_color_red();
    glutSolidCube(scenery[0].size);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(scenery[1].translate_position_x, scenery[1].translate_position_y, scenery[1].translate_position_z);
    //glRotatef(scenery[1].rotate_angle, scenery[1].rotate_position_x, scenery[1].rotate_position_y, scenery[1].rotate_position_z);
    glScalef(scenery[1].scale_position_x, scenery[1].scale_posistion_y, scenery[1].scale_posistion_z);
    set_color_red();
    glutSolidCube(scenery[1].size);
    glPopMatrix();

    glPushMatrix();
    set_color_red();
    glTranslatef(scenery[2].translate_position_x, scenery[2].translate_position_y, scenery[2].translate_position_z);
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
}

void lighting()
{
    GLfloat position[4] = {-1.0f, 1.0f, 0.0f, 0.0f}; //Posição da camêra
    GLfloat white[4]    = {1.0f, 1.0f, 1.0f, 1.0f}; //ùltimo elemento ó ahpa
    GLfloat black[4]    = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    //Ativando ilumina��o
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

}


void set_camera(float positio_x, float posistio_y, float position_z)
{
    gluLookAt(positio_x, posistio_y, position_z, //Posição da câmera
              0, 0, 0, //Para onde  a câmera aponta
              0, 1, 0);
}

void set_color_red(){
    glColor3f(1.0, 0.0, 0.0);
}
void set_color_green(){
    glColor3f(0.0, 1.0, 0.0);
}
void set_color_blue(){
    glColor3f(0.0, 0.0, 1.0);
}
