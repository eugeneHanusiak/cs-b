#include <iostream>
#include "gwindow.h"
using namespace std;

double SIDE_SIZE = 120; //size of the branch at the start of program
const int cycleCount = 7; // density of tree branches
//drawing fractal using recursion
void drawFractal(GWindow gw,GPoint root,double SIDE_SIZE,int cycleCount,double theta){
    //makes green leaves
    if(cycleCount < 2){
        gw.setColor("GREEN");
    }else{
        gw.setColor("GRAY");
    }
    //main branch
    GPoint top = gw.drawPolarLine(root,SIDE_SIZE,theta);

    //drawing polar lines of the main polar line by using recursion
    if(cycleCount >=0){
        drawFractal(gw,top,SIDE_SIZE/1.3,cycleCount-1,theta - 30);
        drawFractal(gw,top,SIDE_SIZE/1.3,cycleCount-1, theta);
        drawFractal(gw,top,SIDE_SIZE/1.3,cycleCount-1, theta + 30);
    }
}

int main() {
    //open a window
    GWindow gw (1000, 600);
    //main branch position by horizon;
    double corner = 90;

    //the sun
    for(int i(0);i<50;i++){
        //set color of rays
        gw.setColor("YELLOW");
        gw.drawPolarLine(100,100,150,i*7.2);
    }
    //set color of sun
    gw.setColor("ORANGE");
    gw.fillOval(50,50,100,100);

    //star point of the tree(root)
    GPoint root(gw.getWidth()/2,gw.getHeight());
    //drawing fractal using recursion
    drawFractal(gw,root,SIDE_SIZE,cycleCount,corner);
    return 0;
}
