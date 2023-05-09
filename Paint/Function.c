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


void mouse(int button, int state, int x, int y) {
    int mode = buffer_get_mode();
    Point_Figure click_down = buffer_get_mouse_down();
    Point_Figure click_up = buffer_get_mouse_up();
    Line_Figure line = {click_down, click_up};
    int t = 10, px, py;

    Point_Figure factor = {1.5, 1.5};

    switch(button) {
        case GLUT_LEFT_BUTTON:
            if(state == GLUT_DOWN) {
                buffer_set_mouse_down(x, y);
                //printf("click down at <%d, %d>\n", x, y);
                switch(mode) {
                case 0:
                    buffer_add_point(x, y);
                    break;

                case 1:
                    buffer_add_line_temp(click_down);
                    break;

                case 2:
                    buffer_add_polygon_temp();
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
                case 6:
                    factor.x = 1 / factor.x;
                    factor.y = 1 / factor.y;
                    buffer_scale_line(factor);
                    break;

                case 7:
                    buffer_scale_line(factor);
                    break;

                case 8:
                    factor.x = 1 / factor.x;
                    factor.y = 1 / factor.y;
                    buffer_scale_polygon(factor);
                    break;

                case 9:
                    buffer_scale_polygon(factor);
                    break;

                case 10:
                    buffer_rotate_line(5);
                    break;

                case 11:
                    buffer_rotate_line(-5);
                    break;

                case 12:
                    buffer_rotate_polygon(5);
                    break;

                case 13:
                    buffer_rotate_polygon(-5);
                    break;

                case 14:
                    buffer_translate_point();
                    break;

                case 15:
                    buffer_translate_line();
                    break;

                case 16:
                    buffer_translate_polygon();
                    break;

                case 17:
                    buffer_remove_point();
                    break;

                case 18:
                    buffer_remove_line();
                    break;

                case 19:
                    buffer_remove_polygon();
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

void menu(int value) {
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

        case 6: // Scale Line -
            buffer_set_mode(6);
            break;

        case 7: // Scale Line +
            buffer_set_mode(7);
            break;

        case 8: // Scale Polygon -
            buffer_set_mode(8);
            break;

        case 9: // Scale Polygon +
            buffer_set_mode(9);
            break;

        case 10: // Rotate Line -
            buffer_set_mode(10);
            break;

        case 11: // Rotate Line +
            buffer_set_mode(11);
            break;

        case 12: // Rotate Polygon -
            buffer_set_mode(12);
            break;

        case 13: // Rotate Polygon +
            buffer_set_mode(13);
            break;

        case 14: // Translate Point
            buffer_set_mode(14);
            break;

        case 15: // Translate Line
            buffer_set_mode(15);
            break;

        case 16: // Translate Polygon
            buffer_set_mode(16);
            break;

        case 17: // Delete Point
            buffer_set_mode(17);
            break;

        case 18: // Delete Line
            buffer_set_mode(18);
            break;

        case 19: // Delete Polygon
            buffer_set_mode(19);
            break;

        case 20: // Exit
            exit(0);
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

void create_menu() {
    int subMenu_createFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Create Point", 0);
    glutAddMenuEntry("Create Line", 1);
    glutAddMenuEntry("Create Polygon", 2);

    int subMenu_SelectFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Select Point", 3);
    glutAddMenuEntry("Select Line", 4);
    glutAddMenuEntry("Select Polygon", 5);

    int subMenu_scaleFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Scale Line -", 6);
    glutAddMenuEntry("Scale Line +", 7);
    glutAddMenuEntry("Scale Polygon -", 8);
    glutAddMenuEntry("Scale Polygon +", 9);

    int subMenu_rotateFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Rotate Line -", 10);
    glutAddMenuEntry("Rotate Line +", 11);
    glutAddMenuEntry("Rotate Polygon -", 12);
    glutAddMenuEntry("Rotate Polygon +", 13);

    int subMenu_translateFigure = glutCreateMenu(menu);
    glutAddMenuEntry("Translate Point", 14);
    glutAddMenuEntry("Translate Line", 15);
    glutAddMenuEntry("Translate Polygon", 16);

    int subMenu_deleteFigiure = glutCreateMenu(menu);
    glutAddMenuEntry("Delete Point", 17);
    glutAddMenuEntry("Delete Line", 18);
    glutAddMenuEntry("Delete Polygon", 19);

    int menu = glutCreateMenu(menu);
    glutAddSubMenu("Create Figure", subMenu_createFigure);
    glutAddSubMenu("Select Figure", subMenu_SelectFigure);
    glutAddSubMenu("Scale Figure", subMenu_scaleFigure);
    glutAddSubMenu("Rotate Figure", subMenu_rotateFigure);
    glutAddSubMenu("Translate Figure", subMenu_translateFigure);
    glutAddSubMenu("Delete Figure", subMenu_deleteFigiure);

    glutAddMenuEntry("Exit", 20);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int select_point(int px, int py, int mx, int my, int t)
{
    if(mx <= px + t && mx >= px - t)
    {
        if(my <= py + t && my >= py - t)
        {
//            Point_Figure point = {px, py};
//            int index = indexOfPointList(buffer.points_buffer, point);
//            buffer.select_index = index;
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
        printf("N�o insercepta!");
        return;
    }
    if(p1.y < y && p2.y < y){
       printf("N�o insercepta!");
       return;

    }
    if(p1.x < x && p2.x < x){
        printf("Não insercepta!");
        return;

    }
    if(p1.y == p2.y){
        printf("N�o insercepta!");
        return;

    }
    if((p1.x > x && p2.x > x) && ((p1.y > y && p2.y < y)) || ((p1.y < y && p2.y > y))){
        printf("N�o insercepta!");
        return;
    }

    int x1 = p1.x + (y - p1.y)*(p2.x - p1.x) /(p2.y - p1.y);

    if(x1 > x){
        printf("Ponto interceptado! insercepta!");
        return;
    }
}
