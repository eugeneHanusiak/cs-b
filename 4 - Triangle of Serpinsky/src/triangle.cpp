#include <iostream>
#include "gwindow.h"
#include <cmath>
using namespace std;

double SIDE_SIZE = 500; // size of the triangle side at start
int cycleCount = 8; //number of triangles in triangl (depth of the fractal)

//draw triangle using recursion
void drawTriangle(GWindow gw, GPoint top, double SIDE_SIZE, int cycleCount){

    //formula of the height if triangle
    double height = sqrt(3) * SIDE_SIZE / 2;

    //cordinates of main triangle top at north
    double topX = top.getX();
    double topY = top.getY();

    //two another tops of the triangle
    GPoint left(topX - height,topY + height);
    GPoint right(topX + height,topY + height);

    //sides of the triangle
    gw.drawLine(top,left);
    gw.drawLine(left,right);
    gw.drawLine(top,right);

    //count of fractal depth(number of triangles in triangle)
    if(cycleCount != 0){

        //cordinates of north tops of the another triangles in the main triangle
        GPoint left(topX - height / 2,topY + height / 2);
        GPoint right(topX + height / 2,topY + height / 2);

        //drawing smaller triangle in main triangle
        drawTriangle(gw,top,SIDE_SIZE / 2,cycleCount - 1);
        drawTriangle(gw,left,SIDE_SIZE / 2,cycleCount - 1);
        drawTriangle(gw,right,SIDE_SIZE / 2,cycleCount - 1);
    }

}

int main() {
    //making a window(width,height)
    GWindow gw (1000, 600);

    //the top point of the main triangle
    GPoint top(gw.getWidth() / 2,gw.getHeight() / 2-((sqrt(3) * SIDE_SIZE) / 2) / 2);

    //drawing main triangle
    drawTriangle (gw,top,SIDE_SIZE,cycleCount);
    return 0;
}
