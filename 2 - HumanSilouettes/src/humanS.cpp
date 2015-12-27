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

//shade of Gray color(almost white);
const int Gray = 14119285;
const int minNumPoints = 1000;
int HumansCount = 0;
int NeighboursCount = 0;

//bool Grid of the image which contains black(true) ana white(false) points according to image
Grid<bool> grid (1000,700);
//read image and set true in grid to pixel that gray or more dark than gray
void createGrid(Grid<bool> &grid,GWindow w,GBufferedImage img){

    for(int i(0);i<img.getWidth();i++){
        for(int j(0);j<img.getHeight();j++){
            if(img.getRGB(i,j) <= Gray ){
                grid.set(j,i,true);
            }else{
                grid.set(j,i,false);
            }
        }
    }
}
//check number of balck points at blur
void CheckBlur(Grid<bool> &grid,MyQueue<point> &blackPoints ){
    while(!blackPoints.isEmpty()){
        point curr = blackPoints.front();
        blackPoints.pop();
        for(int row = curr.row - 1; row <= curr.row + 1; row++){
            for(int column = curr.col - 1; column <= curr.col + 1; column++){
                if(grid.inBounds (row, column) && grid.get (row, column)){
                    point neighbour = makepoint (row, column);

                        blackPoints.push_back(neighbour);
                        NeighboursCount++;
                    grid.set (row, column, false);
                }
            }
        }
    }
    //if blur has neighbours more than minNumPoint we assume that this man
    if(blackPoints.isEmpty() && NeighboursCount > minNumPoints ){
        HumansCount++;
        NeighboursCount = 0;
    } else {
            NeighboursCount = 0;
    }
}
//searching black blures
void searchPeople(Grid<bool>&grid){\
    // array of black points (neighbours) at blur
    MyQueue<point> blackPoints;
    int rows = grid.numRows ();
    int columns = grid.numCols ();
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(grid.get (i, j) == true){
                point black = makepoint(i, j);
                blackPoints.push_back(black);
                //chek number of black ponts at blur
                CheckBlur(grid,blackPoints);
            }
        }
    }
    if(HumansCount==1){
        cout << "There is about " <<HumansCount<< " human on this image." << endl;
    }else{
        cout << "There are about " <<HumansCount<< " humans on this image." << endl;
    }
}

int main() {

    GWindow w;
    GBufferedImage img;
    cout<<"Ente name of the image :  ";
    string s;
    getline(cin,s);
    img.load(s.c_str());
    w.setCanvasSize(img.getWidth(),img.getHeight());
    w.add(&img);
    createGrid(grid,w,img);
    searchPeople(grid);
    return 0;
}
