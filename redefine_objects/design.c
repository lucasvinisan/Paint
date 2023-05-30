#include <GL/glut.h>

typedef struct scenario{
    float translate_position_x, translate_position_y, translate_position_z;
    float rotate_position_x, rotate_position_y, rotate_position_z, rotate_angle;
    float scale_position_x, scale_posistion_y, scale_posistion_z;
    float size;
}Scenario;

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
    Scenario scenerio[3];

    scenerio[0].size = 100.0;
    scenerio[1].size = 100.0;
    scenerio[2].size = 100.0;


    scenerio[0].translate_position_x = -50.0;
    scenerio[0].translate_position_y = 0.0;
    scenerio[0].translate_position_z = -206.0;

    /*scenerio[0].rotate_position_x = 0.0;
    scenerio[0].rotate_position_y = 1.0;
    scenerio[0].rotate_position_z = 0.0;
    scenerio[0].rotate_angle = 40.0;*/

    scenerio[0].scale_position_x  = 5.0;
    scenerio[0].scale_posistion_y = 1.0;
    scenerio[0].scale_posistion_z = 0.2;

    //glScalef(0.3, 2.0, 10.0);

    scenerio[1].translate_position_x = 200.0;
    scenerio[1].translate_position_y = 0.0;
    scenerio[1].translate_position_z = -6.0;

    /*scenerio[1].rotate_position_x = 1.0;
    scenerio[1].rotate_position_y = 0.0;
    scenerio[1].rotate_position_z = 0.0;
    scenerio[1].rotate_angle = 40.0;*/

    scenerio[1].scale_position_x  = 0.2;
    scenerio[1].scale_posistion_y = 1.0;
    scenerio[1].scale_posistion_z = 4.15;

    /*Ch�o*/
    scenerio[2].translate_position_x = -50.0;
    scenerio[2].translate_position_y = -40.0;
    scenerio[2].translate_position_z = 0.0;

    scenerio[2].scale_position_x  = 5.0;
    scenerio[2].scale_posistion_y = 0.2;
    scenerio[2].scale_posistion_z = 4.0;

    //glTranslatef(10, 20, 0);
    //glRotatef(90, 0, 1, 0);
    //glScalef(0.3, 2.0, 10.0);


    glPushMatrix();
    glTranslatef(scenerio[0].translate_position_x, scenerio[0].translate_position_y, scenerio[0].translate_position_z);
    //glRotatef(scenerio[0].rotate_angle, scenerio[0].rotate_position_x, scenerio[0].rotate_position_y, scenerio[0].rotate_position_z);sca
    glScalef(scenerio[0].scale_position_x, scenerio[0].scale_posistion_y, scenerio[0].scale_posistion_z);
    glColor3f(1, 0, 0);
    glutSolidCube(scenerio[0].size);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(scenerio[1].translate_position_x, scenerio[1].translate_position_y, scenerio[1].translate_position_z);
    //glRotatef(scenerio[1].rotate_angle, scenerio[1].rotate_position_x, scenerio[1].rotate_position_y, scenerio[1].rotate_position_z);
    glScalef(scenerio[1].scale_position_x, scenerio[1].scale_posistion_y, scenerio[1].scale_posistion_z);
    glColor3f(1, 0, 0);
    glutSolidCube(scenerio[1].size);
    glPopMatrix();

    glPushMatrix();
    glColor3f(1, 0, 0);
    glTranslatef(scenerio[2].translate_position_x, scenerio[2].translate_position_y, scenerio[2].translate_position_z);
    glScalef(scenerio[2].scale_position_x, scenerio[2].scale_posistion_y, scenerio[2].scale_posistion_z);
    glutSolidCube(scenerio[2].size);
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
