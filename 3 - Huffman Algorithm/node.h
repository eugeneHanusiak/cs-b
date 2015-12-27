#ifndef NODE_H
#define NODE_H
using namespace std;

class Node
{
    public:
     int a;
     unsigned char c;
     int size;
     Node *left, *right;

     Node(){left=right=NULL;}
     Node(int some,unsigned char som,int s){
         a=some;
         c=som;
         size=s;
     }
     Node(Node *L, Node *R)
     {  left =  L;
        right = R;
        a = L->a + R->a;  }
};


#endif // NODE_H

