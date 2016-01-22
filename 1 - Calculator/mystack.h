#ifndef MYSTACK
#define MYSTACK

using namespace std;

template <typename T>

class myStack {
private:
    int count; //index of element
    int capacity; //capacity of the stack
    T *array;// pointer to array where we will save data
    void doubleCapacity();//stack capacity increases twice
public:
    myStack(int = 10);//default capacity of stack
    myStack(const myStack<T> &);
    ~myStack();
    void push(const T&);
    void pop();
    T& top();
    bool empty();
    int size();
};

//constructor
template <typename T>
myStack<T>::myStack(int size) {
    if(size <= 0){
        cout << "!!!!   Incorrect size of the stack     !!!!" << endl;
        exit(1);
    }
    array = new T[size];
    capacity = size;
    count = 0;
}

//copy constructor
template <typename T>
myStack<T>::myStack(const myStack<T>& otherStack) {
    capacity = otherStack.capacity;
    array = new T[capacity];
    count = otherStack.count;
    for(int i = 0; i < capacity; i++) {
        array[i] = otherStack.array[i];
    }
}

//destructor
template <typename T>
myStack<T>::~myStack() {
    delete[] array;
}

//add element to the top of stack
template <typename T>
void myStack<T>::push(const T& value) {
    if(count == capacity ) {
        doubleCapacity();
    }
    array[count] = value;
    count++;
}

//delete top element from the stack
template <typename T>
void myStack<T>::pop() {
    if(count == 0) {
        cout << "!!!!   Stack is empty   !!!!" << endl;
        exit(1);
    }
    count--;
}

//top element of the stack
template <typename T>
T& myStack<T>::top() {
    if(count == 0) {
        cout << "!!!!   Stack is empty   !!!!" <<endl;
        exit(1);
    }
    return array[count - 1];
}

//check the stack is empty
template <typename T>
bool myStack<T>::empty() {
    return count == 0;
}

//the number of elements in the stack
template <typename T>
int myStack<T>::size() {
    return  count;
}

//stack capacity increases twice
template <typename T>
void myStack<T>::doubleCapacity() {
    T* tempArray = array;
    capacity *= 2;
    array = new T[capacity];
    for (int i = 0; i < count; i++) {
        array[i] = tempArray[i];
    }
    delete[] tempArray;
}


#endif // MYSTACK
