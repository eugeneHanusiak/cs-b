#ifndef NODE
#define NODE


struct tochka{
    int row;
    int col;
};
tochka makepoint(int r,int c){
    tochka point = {r,c};
    return point;
}
#endif // NODE

