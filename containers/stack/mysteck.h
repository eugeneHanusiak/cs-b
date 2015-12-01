#include <iostream>
#include <vector>

using namespace std;

template <typename T>

class MyStack {
private:
    vector<T> stack;
public:

    MyStack(int size = 0) {
        stack.reserve(size);
    }

    ~MyStack() {}

    MyStack(const MyStack<T> &);

    void push(T value) {
        stack.push_back(value);
    }

    void pop() {
        if (stack.size() > 0) {
            stack.pop_back();
        }
    }

    int size() {
        return stack.size();
    }

    T &top() {
        if (stack.size() > 0) {
            return stack.back();
        }
    }

    void clear() {
        if (stack.size() > 0) {
            stack.clear();
        }
    }

    bool isEmpty() {
        return stack.size() == 0;
    }

    void print() {
        for (int i = stack.size() - 1; i >= 0; i--) {
            cout <<stack[i] << endl;
        }
    }
};

template <typename T>
MyStack<T>::MyStack(const MyStack<T> & otherStack) {
    int size= otherStack.stack.size();
    for (int i = 0; i < size; i++) {
        stack.push_back(otherStack.stack[i]);
    }
}
