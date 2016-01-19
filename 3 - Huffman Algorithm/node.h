#ifndef NODE_H
#define NODE_H
using namespace std;

//class stores frequency of char in file(int f),symbol or letter, and size of it
//has method that sum frequencies of two node
class Node {
public:
    int f;
    unsigned char c;
    int size;
    Node *left, *right;
    Node() {
        left = right = NULL;
    }
    Node(int some,unsigned char som,int s) {
        f = some;
        c = som;
        size = s;
    }
    Node(Node *L, Node *R) {
        left =  L;
        right = R;
        f = L->f + R->f;
    }
};


#endif // NODE_H

