#include <GL/glut.h>
#include "figures.h"


typedef struct scenery{
    float translate_position_x, translate_position_y, translate_position_z;
    float rotate_position_x, rotate_position_y, rotate_position_z, rotate_angle;
    float scale_position_x, scale_posistion_y, scale_posistion_z;
    float size;
}Scenary;


void design_wall()
{
    Scenary scenery[3];

    scenery[0].size = 200.0;
    scenery[1].size = 200.0;
    scenery[2].size = 200.0;


    /*scenery[0].rotate_position_x = 0.0;
    scenery[0].rotate_position_y = 1.0;
    scenery[0].rotate_position_z = 0.0;
    scenery[0].rotate_angle = 40.0;*/

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

}

void lighting()
{
    GLfloat position[4] = {0.0f, 1.0f, 0.0f, 0.0f}; //Posição da camêra
    GLfloat white[4]    = {1.0f, 1.0f, 1.0f, 1.0f}; //ùltimo elemento ó ahpa
    GLfloat black[4]    = {0.0f, 0.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightfv(GL_LIGHT0, GL_AMBIENT, black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
    glLightfv(GL_LIGHT0, GL_SPECULAR, white);

    //Ativando iluminação
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


void set_camera(float positio_x, float posistio_y, float position_z)
{
    gluLookAt(positio_x, posistio_y, position_z, //Posição da câmera
              0, 0, 0, //Para onde  a câmera aponta
              0, 1, 0);
}




