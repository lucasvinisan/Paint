#include <stdio.h>
#include <GL/glut.h>
#define MAX_POINT 100 //definindo um tamamho m�ximo de n�mero de pontos
#define MAX_LINE 100
#define MAX_FIGURES 100
#define MAX_POLYGON 100
#include "function.h"

/*Falta eu criar uma strutura para onde cada um dos elementos correponder� a uma figura criada*/

int count_click = 0; //Vari�vel global para click do mouse
float y_Position;
float x_Position;
int mode = 0;
int nextPolygon = 1;
Point points[MAX_POINT];
int amout_of_points = 0;

Line lines[MAX_LINE];
int amout_of_line = 0;

//Modificar a fun��o de criar poligon
Polygon_figure polygon[MAX_POLYGON];
int amount_of_polygon = 0;  //N�mero de poligonos


void addPoint(float variabel_x, float variable_y){
    Point newpoint = {variabel_x, variable_y};
    points[amout_of_points] = newpoint;

    amout_of_points++;
}


void designPoint(){
    glPointSize(10.0);
    glBegin(GL_POINTS);
    for(int counter = 0; counter < amout_of_points; counter++)
    {
        glColor3f(1, 0, 0);
        glVertex2f(points[counter].variable_x, points[counter].variable_y); //Localiza��o

    }
    glEnd();
}

void addLines(float variable_x1, float variabel_y1, float variable_x2, float variable_y2){
    lines[amout_of_line]._start.variable_x = variable_x1;
    lines[amout_of_line]._start.variable_y = variabel_y1;

    lines[amout_of_line]._end.variable_x = variable_x2;
    lines[amout_of_line]._end.variable_y = variable_y2;

    amout_of_line++;
}

void designLine(){
    glLineWidth(2.0);
    glBegin(GL_LINES);
    for(int counter = 0; counter < amout_of_line; counter++){
        glColor3f(1, 0, 0);
        glVertex2f(lines[counter]._start.variable_x, lines[counter]._start.variable_y);
        glVertex2f(lines[counter]._end.variable_x, lines[counter]._end.variable_y);
    }
    glEnd();
}

void designPoligon()
{
    for(int counter = 0; counter < amout_of_points; counter++)
    {
        glColor3f(0, 0, 1);
        Polygon_figure current = polygon[counter];
         Point aux;

        glBegin(GL_POLYGON);
            for(int vertex = 0; vertex < current.length; vertex++)
            {
                aux = current.point[vertex];
                glVertex2f(aux.variable_x, aux.variable_y);
            }
        glEnd();
    }
}

void add_Poligon(float variabele_x, float variable_y)
{
    int count = 1;

    Point point = {variabele_x, variable_y};
    Polygon_figure nPolygon;

    if(nextPolygon)
    {
        nPolygon.point[0] = point;
        nPolygon.length = 1;
        nextPolygon = 0;
        amount_of_polygon += 1;
    }

    else
    {
        nPolygon.length++;
        nPolygon = polygon[amount_of_polygon];
        Point *vertex = nPolygon.point;
        vertex[nPolygon.length] = point;


    }
    //polygon[amount_of_polygon].point[amout_of_points].variable_x = variabele_x;
    //polygon[amount_of_polygon].point[amout_of_points].variable_y = variable_y;
}

void mouse(int button, int state, int variable_x, int variable_y)
{


    float scale_factor;

    if(window_width > window_height){
        scale_factor = (window_height / 2.0);
    }else{
        scale_factor = (window_width / 2.0);
    }

    x_Position = ((float)variable_x / scale_factor) - 1.0;
    y_Position = 1.0 - ((float)variable_y / scale_factor);

    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            switch(mode)
            {
                case 0:
                    addPoint(x_Position, y_Position);
                    count_click++;
                    break;

                case 1:
                    addPoint(x_Position, y_Position);
                    addLines(points[amout_of_points - 1].variable_x, points[amout_of_points - 1].variable_y,
                     points[amout_of_points - 2].variable_x, points[amout_of_points - 2].variable_y);
            count_click = 0;
                    break;
                case 2:
                    addPoint(x_Position, y_Position);
                    add_Poligon(x_Position, y_Position);
                    break;
            }

    }
}

void functionMenu(int value)
{
    switch(value)
    {
        case 0:
            mode = 0;
            nextPolygon = 1;
            break;
        case 1:
            mode = 1;
            nextPolygon = 1;
            break;

        case 2:
            mode = 2;
            break;

        case 3:
            exit(0);
            break;
        default:

            break;
    }
    glutPostRedisplay();
}

void createMenu()
{
    glutCreateMenu(functionMenu);
    glutAddMenuEntry("Create point", 0);
    glutAddMenuEntry("Create line", 1);
    glutAddMenuEntry("Create polygon", 2);
    glutAddMenuEntry("Exit", 3);

    glutAttachMenu(GLUT_RIGHT_BUTTON);

}
