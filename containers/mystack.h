#ifndef MYSTACK
#define MYSTACK

using namespace std;

template <typename T>

class MyStack {
private:
    int count; //index of element
    int capacity; //capacity of the stack
    T *array;// pointer to array where we will save data
    void doubleCapacity();//stack capacity increases twice
public:
    MyStack(int = 10);//default capacity of stack
    MyStack(const MyStack<T> &);
    ~MyStack();
    void push(const T&);
    void pop();
    T& top();
    bool empty();
    int size();
};

//constructor
template <typename T>
MyStack<T>::MyStack(int size) {
    if(size <= 0) {
        cout << "!!!!   Incorrect size of the stack     !!!!" << endl;
        exit(1);
    }
    array = new T[size];
    capacity = size;
    count = 0;
}

//copy constructor
template <typename T>
MyStack<T>::MyStack(const MyStack<T>& otherStack) {
    capacity = otherStack.capacity;
    array = new T[capacity];
    count = otherStack.count;
    for(int i = 0; i < capacity; i++) {
        array[i] = otherStack.array[i];
    }
}

//destructor
template <typename T>
MyStack<T>::~MyStack() {
    delete[] array;
}

//add element to the top of stack
template <typename T>
void MyStack<T>::push(const T& value) {
    if(count == capacity ) {
        doubleCapacity();
    }
    array[count] = value;
    count++;
}

//delete top element from the stack
template <typename T>
void MyStack<T>::pop() {
    if(count == 0) {
        cout << "!!!!   Stack is empty   !!!!" << endl;
        exit(1);
    }
    count--;
}

//top element of the stack
template <typename T>
T& MyStack<T>::top() {
    if(count == 0) {
        cout << "!!!!   Stack is empty   !!!!" <<endl;
        exit(1);
    }
    return array[count - 1];
}

//check the stack is empty
template <typename T>
bool MyStack<T>::empty() {
    return count == 0;
}

//the number of elements in the stack
template <typename T>
int MyStack<T>::size() {
    return  count;
}

//stack capacity increases twice
template <typename T>
void MyStack<T>::doubleCapacity() {
    T* tempArray = array;
    capacity *= 2;
    array = new T[capacity];
    for (int i = 0; i < count; i++) {
        array[i] = tempArray[i];
    }
    delete[] tempArray;
}


#endif // MYSTACK

