#ifndef MYQUEUE
#define MYQUEUE

#include <iostream>

using namespace std;

template <typename T>

class MyQueue {
private:
    //struct stores data and pointer to next element in Queue
    struct Node {
        T data;
        Node *next;
    };
    //count of elements in Queue
    int count;
    //pointer to head of Queue
    Node *head;
    //pointer to tail of Queue
    Node *tail;
public:
    MyQueue();
    MyQueue(const MyQueue<T>& otherQueue);
    ~MyQueue();
    void pushBack(const T&);
    void popFront();
    bool isEmpty();
    int size();
    T& front();
    T& back();
    void clear();
};

//Constructor
template <typename T>
MyQueue<T>::MyQueue() {
    head = tail = NULL;
    count = 0;
}

//Copy-constructor
template <typename T>
MyQueue<T>::MyQueue(const MyQueue<T>& otherQueue) {
    if (!otherQueue.isEmpty()) {
        head = tail = 0;
        count = 0;
        for (Node *n = otherQueue.head; n != NULL; n = n->next) {
            pushBack(n->data);
        }
    } else {
        cout << "Error! You trying to copy empty Queue" << endl;
        exit(0);
    }
}
//Destructor
template <typename T>
MyQueue<T>::~MyQueue() {
    clear();
}

//Add element to the end of Queue
template <typename T>
void MyQueue<T>::pushBack(const T& value) {
    Node *n = new Node;
    n->data = value;
    n->next = NULL;
    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        tail->next = n;
        tail = n;
    }
    count++;
}

//Delete the first element from the Queue
template <typename T>
void MyQueue<T>::popFront() {
    if (isEmpty()) {
        cout << "ERROR!!! You trying to pop front empty Queue." << endl;
        exit(0);
    }
    head = head->next;
    if (head == NULL) {
        tail = NULL;
        count = 0;
    } else {
        count--;
    }
}

//Check the Queue is empty
template <typename T>
bool MyQueue<T>::isEmpty() {
    return count == 0;
}

//Return number of elements of the Queue
template <typename T>
int MyQueue<T>::size() {
    return count;
}

//Return first element in the Queue
template <typename T>
T& MyQueue<T>::front() {
    if (isEmpty()) {
        cout << "Can't do 'front'. The Queue is empty." << endl;
        exit(0);
    }
    return head->data;
}

//Return last element in the Queue
template <typename T>
T& MyQueue<T>::back() {
    if (isEmpty()) {
        cout << "Can't do 'back'. The Queue is empty." << endl;
        exit(0);
    }
    return tail->data;
}

//Delete all elements of the Queue(clear Queue)
template <typename T>
void MyQueue<T>::clear() {
    while (head != NULL) {
        head = head->next;
    }
    count = 0;
}

#endif // MYQUEUE

