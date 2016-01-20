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
int humansCount = 0;

//count of black points(neighbours) at blur(human)
int neighboursCount = 0;

//check number of balck points at blur
void checkBlur(GBufferedImage &img, MyQueue<point> &blackPoints ) {
    //if there are not checked black points in queue - take first point in the queue deleting it and searching its neighbours
    while(!blackPoints.isEmpty()) {
        point curr = blackPoints.front();
        blackPoints.popFront();
        //buffer RGB color of every point on image
        int RGB;
        for(int row = curr.row - 1; row <= curr.row + 1; row++) {
            for(int column = curr.col - 1; column <= curr.col + 1; column++) {

                if(row <= img.getWidth() & row >= 0 & column <= img.getHeight() & column >= 0) {
                    //buffer RGB color of every point on image
                    RGB = img.getRGB(row,column);

                    //if neighbour is black set it color white and add to queue of neighbours
                    if(img.getBlue(RGB) <= maxValue & img.getRed(RGB) <= maxValue & img.getGreen(RGB) <= maxValue) {

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
        neighboursCount = 0;
    } else {
        neighboursCount = 0;
    }
}
//searching black blures
void searchPeople(GBufferedImage &img) {
    // array of black points (neighbours) on blur
    MyQueue<point> blackPoints;
    int rows = img.getWidth();
    int columns = img.getHeight();
    //buffer RGB color of every pixel on image
    int RGB;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {

            RGB = img.getRGB(i,j);
            //if intensity of each three colors R,G,B < 50 then we can think that its black point
            if(img.getBlue(RGB) <= maxValue & img.getRed(RGB) <= maxValue & img.getGreen(RGB) <= maxValue) {
                point black = makePoint(i, j);
                blackPoints.pushBack(black);
                //chek number of black points at blur
                checkBlur(img,blackPoints);
            }
        }
    }
    if(humansCount == 1) {
        cout << "There is about " <<humansCount<< " human on this image." << endl;
    }else {
        cout << "There are about " <<humansCount<< " humans on this image." << endl;
    }
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
    searchPeople(img);
    return 0;
}
