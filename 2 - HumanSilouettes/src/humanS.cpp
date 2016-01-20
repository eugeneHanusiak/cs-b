#include <fstream>
#include "windows.h"
#include <iostream>
#include "console.h"
#include "grid.h"
#include "gwindow.h"
#include "gbufferedimage.h"
#include "node.h"
#include "myqueue.h"
using namespace std;

const int WHITE = 16777215;

//max intensity of Red, Green or Blue in pixel to think tha it is black point
const int maxValue = 50;

//minimum number of black points to think that is human(depends of the picture)
const int minNumNeighbours = 400;

//get RBG color of pixel on image and return true when intensity of Red, Green and Blue colors in this pixel less than maxValue
boolean isBlackPoint(int row,int col,GBufferedImage &img) {
    //gets GRB color of pixel
    int rgb = img.getRGB(row,col);
    return (img.getBlue(rgb) <= maxValue & img.getRed(rgb) <= maxValue & img.getGreen(rgb) <= maxValue);
}

//check number of balck points at blur
void checkBlur(GBufferedImage &img, myQueue<point> &blackPoints,int &humansCount) {
    //count of black points(neighbours) at blur(human)
    int neighboursCount = 0;
    //if there are not checked black points in queue - take first point in the queue deleting it and searching its neighbours
    while(!blackPoints.isEmpty()) {
        point curr = blackPoints.front();
        blackPoints.popFront();

        for(int row = curr.row - 1; row <= curr.row + 1; row++) {
            for(int column = curr.col - 1; column <= curr.col + 1; column++) {

                if(row <= img.getWidth() & row >= 0 & column <= img.getHeight() & column >= 0) {

                    //if neighbour is black - set it color white and add to queue of neighbours
                    if(isBlackPoint(row,column,img)) {
                        point neighbour = makePoint (row, column);
                        blackPoints.pushBack(neighbour);
                        neighboursCount++;
                        //set white color to black point
                        img.setRGB(row, column,WHITE);
                    }
                }
            }
        }
    }
    //if queue is empty(all neighbours is checked) and blur has neighbours more than minNumPoint we assume that this man
    if(blackPoints.isEmpty() && neighboursCount > minNumNeighbours ) {
        humansCount++;
    }
}
//searching black blures
int searchPeople(GBufferedImage &img) {
    // array of black points (neighbours) on blur
    myQueue<point> blackPoints;
    int humansCount = 0;
    int rows = img.getWidth();
    int columns = img.getHeight();

    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {

            if(isBlackPoint(i,j,img)) {
                point black = makePoint(i, j);
                blackPoints.pushBack(black);
                //chek number of black points at blur
                checkBlur(img,blackPoints,humansCount);
            }
        }
    }
    return humansCount;
}

int main() {

    GWindow w;
    GBufferedImage img;
    cout<<"Enter name of the image :  ";
    string s;
    getline(cin,s);
    img.load(s.c_str());
    w.setCanvasSize(img.getWidth(),img.getHeight());
    w.add(&img);
    //searching black blures on image
    double humansCount = searchPeople(img);

    if(humansCount == 1) {
        cout << "There is about " <<humansCount<< " human on this image." << endl;
    }else {
        cout << "There are about " <<humansCount<< " humans on this image." << endl;
    }

    return 0;
}
