#ifndef MYMAP
#define MYMAP
#include <iostream>
#include <stdlib.h>
#include "myvector.h"

template<typename KeyType, typename ValueType>
class MyMap{

   public:
    MyMap();
    ~MyMap();
    void put(KeyType, ValueType);
    ValueType get(KeyType);
    bool isEmpty()const;
    void clear();
    int size() const;
    void remove(KeyType);
    KeyType getKey(int);
    bool containsKey(KeyType key);
private:

    struct node {
        KeyType NodeKey;
        ValueType NodeValue;
    };

    /* Vector in which stored value*/
     MyVector<node> r;

    int findKey(KeyType);
};


/* Implementation of all methods of MapSHPP class*/
template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::MyMap(){

}

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::~MyMap(){

}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::put(KeyType key, ValueType value){
    int index = findKey(key);
    if(index == -1){
        node tmpNode;
        tmpNode.NodeKey = key;
        tmpNode.NodeValue = value;
        r.add(tmpNode);

    } else {
        r[index].NodeValue = value;

    }
}

template<typename KeyType, typename ValueType>
int MyMap<KeyType, ValueType>::findKey(KeyType key){
    for(int i = 0; i < r.size(); i++){
        node tmpNode = r.get(i);
        if(tmpNode.NodeKey == key){
            return i;
        }
    }
    return -1;
}

template<typename KeyType, typename ValueType>
ValueType MyMap<KeyType, ValueType>::get(KeyType key){

    int index = findKey(key);
    if(index == -1){
        std::cout << "Error, key not found"<< std::endl;
        exit(1);
    }

    return r[index].NodeValue;

}

template<typename KeyType, typename ValueType>
int MyMap<KeyType, ValueType>::size() const{
    return r.size();
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::remove(KeyType key){
    int index = findKey(key);
    if(index == -1){
        std::cout << "Error, key not found"<< std::endl;
        exit(1);
    }

    r.remove(index);
}

template<typename KeyType, typename ValueType>
bool MyMap<KeyType, ValueType>::isEmpty() const{
    return r.size() == 0;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::clear(){
    r.clear();
}

template<typename KeyType, typename ValueType>
KeyType MyMap<KeyType, ValueType>::getKey(int index){
    return r[index].NodeKey;
}

template<typename KeyType, typename ValueType>
bool MyMap<KeyType, ValueType>::containsKey(KeyType key){
    bool res = true;
    if(findKey(key) == -1) res = false;
    return res;
}

#endif // MYMAP

