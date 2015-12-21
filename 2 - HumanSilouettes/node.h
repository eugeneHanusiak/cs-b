#ifndef NODE
#define NODE


struct point{
    int row;
    int col;
};
point makepoint(int r,int c){
    point point = {r,c};
    return point;
}
#endif // NODE

