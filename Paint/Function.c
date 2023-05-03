#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h>

#include "function.h"
#include "buffer.h"

//Opcodes line

typedef struct {
    unsigned char all;
    unsigned char left;
    unsigned char right;
    unsigned char bottom;
    unsigned char top;
}Outcode;


void preview_line(Line_Figure line)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_LINES);
        glColor3f(0, 1, 0);
        glVertex2f(line.start.x, line.start.y);
        glVertex2f(line.end.x, line.end.y);
    glEnd();

    glDisable(GL_BLEND);
}

void mouse_motion(int x, int y)
{
    int mode = buffer_get_mode();
    Point_Figure click_down = buffer_get_mouse_down();
    Point_Figure click_up = buffer_get_mouse_up();
    Line_Figure line = {click_down, click_up};

    switch(mode)
    {
        case 1:
//            if(!isPointsEquals(click_down, click_up))
//            {
//                preview_line(line);
//            }
            break;

        case 2:
            break;

        default:
            break;
    }
}

void mouse(int button, int state, int x, int y)
{
    int mode = buffer_get_mode();
    Point_Figure click_down = buffer_get_mouse_down();
    Point_Figure click_up = buffer_get_mouse_up();
    Line_Figure line = {click_down, click_up};
    int t = 10, px, py;


    switch(button)
    {
    case GLUT_LEFT_BUTTON:
        if(state == GLUT_DOWN)
        {
            buffer_set_mouse_down(x, y);
            //printf("click down at <%d, %d>\n", x, y);
            switch(mode)
            {
            case 0:
                buffer_add_point(x, y);
                break;
            case 1:
                buffer_add_line_temp(click_down);
                break;
            case 3:
                px = click_down.x;
                py = click_down.y;
                select_point(px, py, x, y, t);
                break;
            case 4:

                selectLine(line.start.x, line.end.x, line.start.y, line.end.y,
                           3, 2, 3, 2);
                           printf("%d %d %d %d \n", click_down.x, line.end.x, line.start.y, line.end.y);
                break;
            default:
                break;
            }
        }

        else if(state == GLUT_UP)
        {
            //printf("click up at <%d, %d>\n", x, y);
            buffer_set_mouse_up(x, y);
        }

        break;
    }
}

void menu(int value)
{
    switch(value)
    {
        case 0: // Add Point
            buffer_set_mode(0);
            break;

        case 1: // Add Line
            buffer_set_mode(1);
            break;

        case 2: // Add Polygon
            buffer_set_mode(2);
            break;

        case 3: // Select Point
            buffer_set_mode(3);
            break;

        case 4: // Select Line
            buffer_set_mode(4);
            break;

        case 5: // Select Polygon
            buffer_set_mode(5);
            break;

        case 6: // Scale Point
            buffer_set_mode(6);
            break;

        case 7: // Scale Line
            buffer_set_mode(7);
            break;

        case 8: // Scale Polygon
            buffer_set_mode(8);
            break;

        case 9: // Rotate Point
            buffer_set_mode(9);
            break;

        case 10: // Rotate Line
            buffer_set_mode(10);
            break;

        case 11: // Rotate Polygon
            buffer_set_mode(11);
            break;

        case 12: // Translate Point
            buffer_set_mode(12);
            break;

        case 13: // Translate Line
            buffer_set_mode(14);
            break;

        case 14: // Translate Polygon
            buffer_set_mode(14);
            break;

        case 15: // Delete Point
            buffer_set_mode(15);
            break;

        case 16: // Delete Line
            buffer_set_mode(16);
            break;

        case 17: // Delete Polygon
            exit(0);
            break;

        case 18: // Exit
            exit(0);
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

void create_menu()
{
    int subMenu_createFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Create Point", 0);
    glutAddMenuEntry("Create Line", 1);
    glutAddMenuEntry("Create Polygon", 2);

    int subMenu_SelectFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Select Point", 3);
    glutAddMenuEntry("Select Line", 4);
    glutAddMenuEntry("Select Polygon", 5);

    int subMenu_scaleFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Scale Point", 6);
    glutAddMenuEntry("Scale Line", 7);
    glutAddMenuEntry("Scale Polygon", 8);

    int subMenu_rotateFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Rotate Point", 9);
    glutAddMenuEntry("Rotate Line", 10);
    glutAddMenuEntry("Rotate Polygon", 11);

    int subMenu_translateFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Translate Point", 12);
    glutAddMenuEntry("Translate Line", 13);
    glutAddMenuEntry("Translate Polygon", 14);

    int subMenu_deleteFigiure = glutCreateMenu(menu);
    glutAddMenuEntry("Delete Point", 15);
    glutAddMenuEntry("Delete Line", 16);
    glutAddMenuEntry("Delete Polygon", 17);

    int menu = glutCreateMenu(menu);
    glutAddSubMenu("Create Figure", subMenu_createFigure);
    glutAddSubMenu("Select Figure", subMenu_SelectFigure);
    glutAddSubMenu("Scale Figure", subMenu_scaleFigure);
    glutAddSubMenu("Rotate Figure", subMenu_rotateFigure);
    glutAddSubMenu("Translate Figure", subMenu_rotateFigure);
    glutAddSubMenu("Delete Figure", subMenu_deleteFigiure);

    glutAddMenuEntry("Exit", 18);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}


int select_point(int px, int py, int mx, int my, int t)
{
    if(mx <= px + t && mx >= px - t)
    {
        if(my <= py + t && my >= py - t)
            {
            printf("Ponto selecionado!\n");
            return 1;
        }
    }
}


Outcode generateCode(int x, int y, int xmin, int xmax, int ymin, int ymax)
{
    Outcode code;
    code.top = 0;
    code.all = 0;
    code.bottom = 0;
    code.right = 0;
    code.left = 0;

    if(y > ymax){
        code.top = 1;
        code.all+=8;
    }else if(y < ymin){
        code.bottom = 2;
        code.all += 4;
    }
    if(x > xmax){
        code.right = 1;
        code.all += 2;
    }else if(x < xmin){
        code.left = 1;
        code.all += 1;
    }
    return code;
}

void selectLine(int x0, int x1, int y0, int y1, int xmin, int xmax, int ymin, int ymax)
{
    Outcode outcode0, outcode1, OutcodeOut, generateCode();
    int accept = 0, done = 0;
    int x_position, y_position;

    outcode0 = generateCode(x0, y0, xmin, xmax, ymin, ymax);
    outcode1 = generateCode(x0, y0, xmin, xmax, ymin, ymax);


    do{
        if(outcode0.all == 0 && outcode1.all == 0)
        {
            done = 1, accept = 1;
        }else if((outcode0.all & outcode1.all) != 0){
            done = 1;
        }else{
            if(OutcodeOut.all != 0){
                OutcodeOut = outcode0;
                printf("Linha selecionada!");
            }else{
                OutcodeOut = outcode1;
            }
            if(OutcodeOut.top){
                x_position = x0 + (x1 - x0) * (ymax - y0) / (y1 - y0);
                y_position = ymax;
            }
            else if(OutcodeOut.bottom){

                x_position = x0 + (x1 - x0) * (ymin - y0) / (y1 - y0);
                y_position = ymin;
            }
            else if(OutcodeOut.right){
                y_position = x0 + (x1 - x0) * (xmax - y0) / (y1 - y0);
                x_position = xmax;
            }
            else if(OutcodeOut.left){
                y_position = x0 + (x1 - x0) * (xmin - y0) / (y1 - y0);
                x_position = xmin;
            }

            if(OutcodeOut.all == outcode0.all){
                x0 = x_position;
                y0 = y_position;
                outcode0 = generateCode(x0, y0, xmin, xmax, ymin, ymax);

            }else{
                x1 = x_position;
                y1 = y_position;
                outcode1 = generateCode(x1, y1, xmin, xmax, ymin, ymax);
            }
        }
    }while(!done);
}
//X e y coordenadas dos pontos

void select_polygon(POINT p1, POINT p2, int x, int y)
{
    if(p1.y > y && p2.y > y){
        printf("Não insercepta!");
        return;
    }
    if(p1.y < y && p2.y < y){
       printf("Não insercepta!");
       return;

    }
    if(p1.x < x && p2.x < x){
        printf("Não insercepta!");
        return;

    }
    if(p1.y == p2.y){
        printf("Não insercepta!");
        return;

    }
    if((p1.x > x && p2.x > x) && ((p1.y > y && p2.y < y)) || ((p1.y < y && p2.y > y))){
        printf("Não insercepta!");
        return;
    }

    int x1 = p1.x + (y - p1.y)*(p2.x - p1.x) /(p2.y - p1.y);

    if(x1 > x){
        printf("Ponto interceptado! insercepta!");
        return;
    }
}
