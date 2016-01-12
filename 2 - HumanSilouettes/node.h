#ifndef NODE
#define NODE

//struct that stores row and column of point
struct point{
    int row;
    int col;
};
//makes point with row - r and col - c
point makepoint(int r,int c){
    point point = {r,c};
    return point;
}
#endif
