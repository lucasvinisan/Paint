#ifndef FUNCTION_H_INCLUDED
#define FUNCTION_H_INCLUDED/*estrutura do ponto que ser� criado*/
#define window_width 600.0
#define window_height 600.0
#define MAX_POINT 1000
#define MAX_LINE 1000
#define MAX_FIGURES 1000
#define MAX_PENTAGON 1000

/*Estrutura de um ponto*/
typedef struct
{
    float variable_x;
    float variable_y;
}Point;

/*Estrutura de uma reta*/
typedef struct
{
    Point _start;
    Point _end;
}Line;

typedef struct
{
    Point point[MAX_POINT];
}Polygon_figure;

//Fun��o para adicionar um ponto
void addPoint(float variabel_x, float varible_y);

//Fun��o para desenhar um ponto
void designPoint();

//Fun��o para adicionar um reta
void addLines(float variable_x1, float variabel_y1, float variable_x2, float variable_y2);

//Fun��o para desenhar uma reta
void designLine();

/*Pegar evento do mouse*/
void mouse(int button, int state, int variable_x, int variable_y);

void createMenu();



#endif // FUNCTION_H_INCLUDED
