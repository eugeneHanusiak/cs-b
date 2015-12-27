#ifndef MYQUEUE
#define MYQUEU

#include <vector>
#include <iostream>
#include "node.h"

using namespace std;

template <typename T>

class MyQueue {
private:
    int queueSize; // the size of the queue (number of elements)
    int begin, end; // the point of the begin and the end of the queue
    vector<T> queue;
public:
    MyQueue(int = 10); // default size of the queue = 10
    MyQueue(const MyQueue<T> &); // copy constructor
    ~MyQueue();
    void push_back(T);
    void pop();
    T &front();
    T &back();
    void clear();
    int size();
    bool isEmpty();
    void operator=(const MyQueue<T> &);
};

template <typename T>
MyQueue<T>::MyQueue(int s) {
    queueSize = s;
    begin = 0;
    end = 0;
    queue.reserve(queueSize);
}

template <typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& otherMyQueue) {
    queueSize = otherMyQueue.queueSize;
    begin = otherMyQueue.begin;
    end = otherMyQueue.end;
    //copy elements from current queue to other
    queue.reserve(queueSize);
    for (int i = 0; i < queueSize; i++) {
        queue.push_back(otherMyQueue.queue[i]);
    }
}

template <typename T>
MyQueue<T>::~MyQueue() {
}

template <typename T>
void MyQueue<T>::push_back(T elem) {
    queue.push_back(elem);
    end++;
    queueSize = queue.size();
}

template <typename T>
void MyQueue<T>::pop() {
    //check the number of elements
    if (queueSize > 0) {
        //delete first element
        queue.erase(queue.begin());
        end--;
        queueSize = queue.size();
    }
}

template <typename T>
T &MyQueue<T>::front() {
    T *frontElem;
    if (queueSize > 0) {
        frontElem = &queue[begin];
    }
    return *frontElem;
}

template <typename T>
T &MyQueue<T>::back() {
    T *EndElem;
    if (queueSize > 0) {
        EndElem = &queue[end - 1];
    }
    return *EndElem;
}

template <typename T>
void MyQueue<T>::clear() {
    if (queue.size() > 0) {
        begin = 0;
        end = 0;
        queueSize = 0;
        queue.clear();
    }
}

template <typename T>
int MyQueue<T>::size() {
    return queueSize;
}

template <typename T>
bool MyQueue<T>::isEmpty() {
    return queueSize == 0;
}

#endif // MYQUEUE

