#ifndef MYVECTOR
#define MYVECTOR

using namespace std;

template<typename T>
class myVector{

public:
    myVector();
    myVector(int s);
    myVector(const myVector<T> & src);
    myVector<T> & operator=(const myVector<T> & src);
    ~myVector();
    //adds T value to the end of vector
    void pushBack(T);
    //remove last element in vector
    void PopBack();
    //clear vector
    void clear();
    // Inserts element in vector in the specified index
    bool isEmpty() const;
    // Removes value at index int
    void remove(int);
    //set value T to the index int
    void set(int, T);
    //return int size of vector
    int size() const;
    //takes element at[int] position in vector
    T & operator[](int);

private:
    T *array;
    int Size;
    //number of the element in array
    int count;
    static const int initSize = 2;
    void extendArray();
};
//Constructor
template<typename T>
myVector<T>::myVector() {
    array = new T[initSize];
    Size = initSize;
    count = 0;
}
template<typename T>
myVector<T>::myVector(int s) {
    array = new T[s];
    Size = s;
    count = s;
}
template<typename T>
T & myVector<T>::operator[](int index) {
    if(index < 0 || index >= count){
        cout << "!!!!   Index is not correct   !!!!" <<index<<endl;
        exit(1);
    }
    return array[index];
}
template<typename T>
void myVector<T>::pushBack(T value) {
    if (count == Size) {
        extendArray();
    }
    array[count] = value;
    count++;
}
template<typename T>
void myVector<T>::PopBack() {
    if(count >= 0){

        count--;
    }else{
        cout<<"Vector is EMPTY"<<endl;
    }\
}
template <typename T>
void myVector<T>::clear() {
    count = 0;
}

template <typename T>
bool myVector<T>::isEmpty() const {
    return count == 0;
}

template <typename T>
void myVector<T>::remove(int index) {
    if(index < 0 || index >= count) {
        cout << "!!!!   Index is not correct   !!!!" <<endl;
        exit(1);
    }
    for(int i = index; i < count-1; i++) {
        array[i] = array[i+1];
    }
    count--;
}

template <typename T>
void myVector<T>::set(int index, T value) {
    if(index < 0 || index >= count){
        cout << "!!!!   Index is not correct   !!!!" << endl;
        exit(1);
    }
    array[index] = value;
}

template <typename T>
int myVector<T>::size() const {
    return count;
}

template <typename T>
void myVector<T>::extendArray() {
    T *oldArray = array;
    Size *= 2;
    array = new T[Size];
    for (int i = 0; i < count; i++) {
        array[i] = oldArray[i];
    }
    delete[] oldArray;
}
//Copy constructor
template<typename T>
myVector<T>::myVector(const myVector<T> & src) {
    this->array = new T[src.Size];
    count = src.count;
    Size = src.Size;
    for (int i = 0; i < src.count; i++) {
        array[i] = src.array[i];
    }
}
//function of operator '='
template<typename T>
myVector<T> & myVector<T>::operator =(const myVector<T> & src) {
    delete[] array;
    this->array = new T[src.Size];
    count = src.count;
    Size = src.Size;
    for (int i = 0; i < src.count; i++) {
        array[i] = src.array[i];
    }
    return *this;
}
//destructor
template<typename T>
myVector<T>::~myVector() {
    count = 0;
    delete [] array;
}

#endif // MYVECTOR
