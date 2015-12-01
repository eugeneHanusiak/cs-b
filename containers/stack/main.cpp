#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "mysteck.h"

using namespace std;

int main()
{
    MyStack<int>one=10;
    one.push(547);

    if(one.isEmpty()){
        cout<<"EMPTY"<<endl;
    };


    MyStack <int> t=one;
    t.print();
    t.push(2345);

    one=t;
    one.print();

    MyStack<string> two;
    two.push("HELLO");
    two.print();

    return 0;
}

