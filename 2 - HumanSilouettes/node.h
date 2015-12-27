#ifndef NODE
#define NODE


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
