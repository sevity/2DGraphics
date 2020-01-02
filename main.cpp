#include <SFML/Graphics.hpp>
#include <math.h>
using namespace std;
using namespace sf;

#define SCREEN_WIDTH (800)
#define SCREEN_HEIGHT (600)
#define CENTER_X (SCREEN_WIDTH/2)
#define CENTER_Y (SCREEN_HEIGHT/2)
#define BOX_LEN (300)

struct Point
{
    double x;
    double y;
};

struct Box
{
    Point p[4];
};

Box box = {
    {{-BOX_LEN/2,-BOX_LEN/2},
    {BOX_LEN/2,-BOX_LEN/2},
    {BOX_LEN/2,BOX_LEN/2},
    {-BOX_LEN/2,BOX_LEN/2}}
};


void draw_line(RenderWindow& window, double x1, double y1, double x2, double y2)
{

    Vertex line[] = {
        Vertex(Vector2f(x1,y1)),
        Vertex(Vector2f(x2,y2))};
    line[0].color=Color::White;
    line[1].color=Color::White;
    window.draw(line, 2, Lines);
}


void draw_box(RenderWindow& window, double cx, double cy)
{
    draw_line(window, cx+box.p[0].x, cy+box.p[0].y, cx+box.p[1].x, cy+box.p[1].y);
    draw_line(window, cx+box.p[1].x, cy+box.p[1].y, cx+box.p[2].x, cy+box.p[2].y);
    draw_line(window, cx+box.p[2].x, cy+box.p[2].y, cx+box.p[3].x, cy+box.p[3].y);
    draw_line(window, cx+box.p[3].x, cy+box.p[3].y, cx+box.p[0].x, cy+box.p[0].y);
}

// P is inout
void matmul2x2(double M[2][2], double P[2])
{
    double x = M[0][0] * P[0] + M[1][0] * P[1];
    double y = M[0][1] * P[0] + M[1][1] * P[1];
    P[0]=x,P[1]=y;
}

void rotate_point(RenderWindow& window, double ang, int ix)
{
    #define PI 3.1415926
    double M[2][2] = 
    {
        {cos(ang), -sin(ang)},
        {sin(ang), cos(ang)}
    };
    double p[2] = {box.p[ix].x,box.p[ix].y};
    matmul2x2(M,p);
    box.p[ix].x=p[0],box.p[ix].y=p[1];
}

void rotate_box(RenderWindow& window, double ang)
{
    for(int i=0;i<4;i++) rotate_point(window, ang, i);
}


int main(void)
{
    RenderWindow window(VideoMode(SCREEN_WIDTH,SCREEN_HEIGHT), "2D");
    while(window.isOpen())
    {
        Event e;
        while(window.pollEvent(e))
        {
            if(e.type==Event::Closed) window.close();
        }
        window.clear(Color(0x000000));
        draw_line(window, 0,CENTER_Y, SCREEN_WIDTH, CENTER_Y);
        draw_line(window, CENTER_X,0, CENTER_X, SCREEN_HEIGHT);
        //rotate_box(window, 3.1415926/4);
        rotate_box(window, 0.0001);
        draw_box(window,CENTER_X, CENTER_Y);

        window.display();
    }
    return 0;
}

