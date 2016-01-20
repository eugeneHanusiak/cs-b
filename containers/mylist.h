#ifndef MYLIST
#define MYLIST
using namespace std;

template <typename T>

class MyList {
private:
    //struct stores data and pointers to previous and next element in list
    struct Node {
        T data;
        Node *next;
        Node *prev;
    };
    //count of elements in list
    int count;
    //pointer to head of list
    Node *head;
    //pointer to tali of list
    Node *tail;
public:
    MyList();
    MyList(const MyList<T>& otherList);
    ~MyList();
    void push_front(const T&);
    void push_back(const T&);
    void pop_front();
    void pop_back();
    bool empty();
    int size();
    T& front();
    T& back();
    void clear();
    typedef Node* iterator;
    iterator begin();
    iterator end();
    void insert(iterator, const T&);
    void erase(iterator);
    void sort();
};

/*constructor*/
template <typename T>
MyList<T>::MyList() {
    head = tail = NULL;
    count = 0;
}

/*copy-constructor*/
template <typename T>
MyList<T>::MyList(const MyList<T>& otherList) {
    if (!otherList.empty()) {
        head = tail = 0;
        count = 0;
        for (Node *n = otherList.head; n != NULL; n = n->next) {
            push_back(n->data);
        }
    } else {
        cerr << "Error! You trying to copy empty list" << endl;
        exit(0);
    }
}
/*destructor*/
template <typename T>
MyList<T>::~MyList() {
    clear();
}

/*add element to the start of list*/
template <typename T>
void MyList<T>::push_front(const T& value) {
    Node *n = new Node;
    n->data = value;
    n->next = NULL;
    n->prev = NULL;
    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        n->next = head;
        head->prev = n;
        head = n;
    }
    count++;
}

/*add element to the end of list*/
template <typename T>
void MyList<T>::push_back(const T& value) {
    Node *n = new Node;
    n->data = value;
    n->next = NULL;
    n->prev = NULL;
    if (head == NULL) {
        head = n;
        tail = n;
    } else {
        n->prev = tail;
        tail->next = n;
        tail = n;
    }
    count++;
}

/*delete the first element from the list*/
template <typename T>
void MyList<T>::pop_front() {
    if (empty()) {
        cerr << "ERROR!!! You trying to pop front empty list." << endl;
        exit(0);
    }
    head = head->next;
    if (head == NULL) {
        tail = NULL;
        count--;
    } else {
        head->prev = NULL;
        count--;
    }
}

/*delete last element from the list*/
template <typename T>
void MyList<T>::pop_back() {
    if (empty()) {
        cerr << "ERROR!!!You trying to po back empty list." << endl;
        exit(0);
    }
    tail = tail->prev;
    if (tail == NULL) {
        head = NULL;
    } else {
        tail->next = NULL;
        count--;
    }
}

/*check the list is empty*/
template <typename T>
bool MyList<T>::empty() {
    return count == 0;
}

/*return number of elements of the list*/
template <typename T>
int MyList<T>::size() {
    return count;
}

/*return first element in the list*/
template <typename T>
T& MyList<T>::front() {
    if (empty()) {
        cerr << "Can't do 'front'. The list is empty." << endl;
        exit(0);
    }
    return head->data;
}

/*return last element in the list*/
template <typename T>
T& MyList<T>::back() {
    if (empty()) {
        cerr << "Can't do 'back'. The list is empty." << endl;
        exit(0);
    }
    return tail->data;
}

/*pointer to the start of the list*/
template <typename T>
typename MyList<T>::iterator MyList<T>::begin() {
    return head;
}

/*Pointer to the end of the list*/
template <typename T>
typename MyList<T>::iterator MyList<T>::end() {
    return tail;
}

/*delete all elements of the list(clear list)*/
template <typename T>
void MyList<T>::clear() {
    while (head) {
        head->prev = NULL;
        head = head->next;
    }
    count = 0;
}

/*insert element to the list in current position using iterator*/
template <typename T>
void MyList<T>::insert(iterator it, const T& value) {
    if (empty()) {
        cerr << "Can't 'insert'. The list is empty." << endl;
        exit(0);
    }
    if (it == begin()) {
        push_front(value);
    } else if (it == end()) {
        push_back(value);
    } else if (it != NULL) {
        Node *n = new Node;
        n->data = value;
        n->next = it;
        n->prev = it->prev;
        it->prev->next = n;
        it->prev = n;
        count++;
    } else {
        cerr << "Can't 'insert'. Iterator is out of range." << endl;
        exit(0);
    }
}

/*delete element from the list from the current position using iterator*/
template <typename T>
void MyList<T>::erase(iterator it) {
    if (empty()) {
        cerr << "Can't 'erase'. The list is empty." << endl;
        exit(0);
    }
    if (it == begin()) {
        pop_front();
    } else if (it == end()) {
        pop_back();
    } else if (it != NULL) {
        Node *n = it->prev;
        Node *m = it->next;
        it = it->next;
        n->next = m;
        m->prev = n;
        count--;
    } else {
        cerr << "Can't 'erase'. Iterator is out of range." << endl;
        exit(0);
    }
}
template <typename T>
/*sorting elements in list*/
void MyList<T>::sort() {
    if (empty()) {
        cerr << "Can't 'insert'. The list is empty." << endl;
        exit(0);
    }
    if (head != 0) {
        Node* current = head;
        Node* prev = 0;
        Node* tempNode = 0;
        int changeFlag = 0;
        for (int i = 0; i < size(); i++) {
            while (current->next != 0) {
                tempNode = current->next;

                if (current->data->f > tempNode->data->f) {
                    changeFlag = 1;
                    current->next = tempNode->next;
                    tempNode->next = current;
                    if (prev != 0)
                        prev->next = tempNode;
                    prev = tempNode;
                    if (head == current)
                        head = tempNode;
                    if (current->next == 0)
                        tail = current;
                }else {
                    prev = current;
                    current = current->next;
                }
            }
            if (changeFlag == 0) {
                break;
            }else {
                prev = 0;
                current = head;
                changeFlag = 0;
            }
        }
    }
}
#endif // MYLIST
