#ifndef MYMAP
#define MYMAP

#include <iostream>
#include <stdlib.h>
#include <vector>
using namespace std;

template<typename KeyType, typename ValueType>
class MyMap{

public:

    MyMap();
    ~MyMap();
    void push(KeyType, ValueType);
    bool isEmpty();
    void clear();
    int size() const;
    ValueType getKey(KeyType);
    bool containsKey(KeyType key);

private:

    struct node {
        KeyType Key;
        ValueType Value;
    };
     //Vector in which will store value
      vector<node> map ;
      bool findKey(KeyType);
};

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::MyMap(){
}

template<typename KeyType, typename ValueType>
MyMap<KeyType, ValueType>::~MyMap(){
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::push(KeyType key, ValueType value){
    if(!findKey(key)){
        node tmpNode;
        tmpNode.Key = key;
        tmpNode.Value = value;
        map.push_back(tmpNode);
    }
}

template<typename KeyType, typename ValueType>
bool MyMap<KeyType, ValueType>::findKey(KeyType key){
    for(int i = 0; i < map.size(); i++){
        node tmp = map[i];
        if(tmp.Key == key){
            return true;
        }
    }
    return false;
}

template<typename KeyType, typename ValueType>
ValueType MyMap<KeyType, ValueType>::getKey(KeyType key){
    if(!findKey(key)){
        cout << "Error!!! key not found"<< endl;
        exit(1);
    }
    for(int i = 0; i < map.size(); i++){
        node tmp = map[i];
        if(tmp.Key == key){
    return map[i].Value;
        }
    }
    return 0;
}

template<typename KeyType, typename ValueType>
int MyMap<KeyType, ValueType>::size() const{
    return map.size();
}

template<typename KeyType, typename ValueType>
bool MyMap<KeyType, ValueType>::isEmpty(){
    return map.size() == 0;
}

template<typename KeyType, typename ValueType>
void MyMap<KeyType, ValueType>::clear(){
    map.clear();
}

template<typename KeyType, typename ValueType>
bool MyMap<KeyType, ValueType>::containsKey(KeyType key){
    if(findKey(key)){
    return true;
    }
    return false;
}

#endif // MYMAP

