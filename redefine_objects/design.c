#include <GL/glut.h>

typedef struct scenery{
    float translate_position_x, translate_position_y, translate_position_z;
    float rotate_position_x, rotate_position_y, rotate_position_z, rotate_angle;
    float scale_position_x, scale_posistion_y, scale_posistion_z;
    float size;
}Scenary;

void design_Teapot()
{
    glTranslatef(-200, 2, 100);
    glColor3f(0, 1, 1);
    glutSolidTeapot(40); //Tamanho do bule que aparecer� na tela
}

void design_Sphere()
{
    glTranslatef(50, 10, 100);
    glColor3f(1.0, 1.0, 0.0);
    glutSolidSphere(40, 100, 10);
}

void design_torus()
{
    glTranslatef(-50, -15, -60);
    glRotatef(90, 1, 0, 0); //Rotaciona 90 graus em torno do eixo x
    glColor3f(0, 1, 0);
    glutSolidTorus(15, 40, 100, 100);
}

void design_wall()
{
    Scenary scenery[3];

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
    scenery[1].scale_posistion_z = 4.15;

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
    glColor3f(1, 0, 0);
    glutSolidCube(scenery[0].size);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(scenery[1].translate_position_x, scenery[1].translate_position_y, scenery[1].translate_position_z);
    //glRotatef(scenery[1].rotate_angle, scenery[1].rotate_position_x, scenery[1].rotate_position_y, scenery[1].rotate_position_z);
    glScalef(scenery[1].scale_position_x, scenery[1].scale_posistion_y, scenery[1].scale_posistion_z);
    glColor3f(1, 0, 0);
    glutSolidCube(scenery[1].size);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(scenery[2].translate_position_x, scenery[2].translate_position_y, scenery[2].translate_position_z);
    glScalef(scenery[2].scale_position_x, scenery[2].scale_posistion_y, scenery[2].scale_posistion_z);
    glutSolidCube(scenery[2].size);
    glPopMatrix();
}


void createmenu()
{
    glutAddMenuEntry("Create Figure 3D", 1);
    glutAddMenuEntry("Add light", 2);
    glutAddMenuEntry("Exit", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
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

    //Ativando ilumina��o
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

}
