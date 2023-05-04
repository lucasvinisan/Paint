#include <stdlib.h>
#include <stdio.h>
#include <gl/glut.h>

#include "function.h"
#include "buffer.h"

void keyboardSpecial(int key, int x, int y) {
    int mode = buffer_get_mode();

}

void keyboard(unsigned char key, int x, int y) {
    Point_Figure factor = {1.5, 1.5};

    switch(key) {
        case 'q':
            buffer_scale_line(factor);
            printf("'q' key pressed\n");
            break;

        case 'e':
            factor.x = -1.5;
            factor.y = -1.5;
            buffer_scale_line(factor);
            printf("'e' key pressed\n");
            break;

        default:
            break;
    }
}

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
                    buffer_rotate_line(15);
                    break;

                case 11:
                    buffer_rotate_line(-15);
                    break;

                case 12:
                    buffer_rotate_polygon(15);
                    break;

                case 13:
                    buffer_rotate_polygon(-15);
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

void select_point(int px, int py, int mx, int my, int t) {
    if(mx <= px + t && mx >= px - t)
    {
        if(my <= py + t && my >= py - t)
            {
            printf("Ponto selecionado!\n");
        }
    }else{
        printf("Nenhum ponto selecionado!\n");
    }
}

void select_line(int px, int py, int mx, int my, int t) {

}

void select_polygon() {

}
