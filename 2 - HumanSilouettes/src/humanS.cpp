#include <fstream>
#include "windows.h"
#include <iostream>
#include "console.h"
#include "strlib.h"
#include "grid.h"
#include "gwindow.h"
#include "gbufferedimage.h"
#include <queue>
#include "node.h"

using namespace std;

const int Gray = 14145495;
int numberOfHumans=0;
int count;

Grid<bool> grid (1000,700);



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


void searchHuman(Grid<bool> &grid,queue<tochka> &blackPoints ){
    while(!blackPoints.empty ()){

        tochka curr = blackPoints.front ();
        blackPoints.pop ();

        for(int row = curr.row - 1; row <= curr.row + 1; row++){
            for(int column = curr.col - 1; column <= curr.col + 1; column++){

                if(grid.inBounds (row, column) && grid.get (row, column)){
                    tochka neighbour = makepoint (row, column);
                    blackPoints.push (neighbour);
                    count++;
                    grid.set (row, column, false);
                }
            }
        }
    }
    if(blackPoints.empty()){
        numberOfHumans++;
        count = 0;
    }
}

void searchPeople(Grid<bool>&grid){
    queue<tochka> blackPoints;

    int rows = grid.numRows ();
    int columns = grid.numCols ();

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            if(grid.get (i, j) == true){
                tochka black = makepoint(i, j);
                blackPoints.push (black);
                searchHuman(grid,blackPoints);
            }
        }
    }
    if(numberOfHumans==1){
        cout << "There is about " <<numberOfHumans<< " human on this image." << endl;
    }else{
        cout << "There are about " <<numberOfHumans<< " humans on this image." << endl;

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

