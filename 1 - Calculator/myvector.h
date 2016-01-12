#ifndef MYVECTOR
#define MYVECTOR

using namespace std;

template<typename T>
class MyVector{

public:
    MyVector();
    MyVector(const MyVector<T> & src);
    MyVector<T> & operator=(const MyVector<T> & src);
    ~MyVector();
    //adds T value to the end of vector
    void pushBack(T);
    //reset count of elements in array to zero(clear array)
    void clear();
    //check for empty
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
    static const int initSize = 10;
    void extendArray();
};
//Constructor
template<typename T>
MyVector<T>::MyVector(){
    array = new T[initSize];
    Size = initSize;
    count = 0;
}
template<typename T>
T & MyVector<T>::operator[](int index){
    if(index < 0 || index >= count){
        cout << "!!!!   Index is not correct   !!!!" <<endl;
        exit(1);
    }
    return array[index];
}

template<typename T>
void MyVector<T>::pushBack(T value){
    //if count of elements in array stay at the last element - array extending
    if (count == Size) {
        extendArray();
    }
    array[count] = value;
    count++;
}

template <typename T>
void MyVector<T>::clear(){
    count = 0;
}

template <typename T>
bool MyVector<T>::isEmpty() const{
    return count == 0;
}

template <typename T>
void MyVector<T>::remove(int index){
    if(index < 0 || index >= count){
        cout << "!!!!   Index is not correct   !!!!" <<endl;
        exit(1);
    }
    for(int i = index; i < count-1; i++){
        array[i] = array[i+1];
    }
    count--;
}

template <typename T>
void MyVector<T>::set(int index, T value){
    if(index < 0 || index >= count){
        cout << "!!!!   Index is not correct   !!!!" << endl;
        exit(1);
    }
    array[index] = value;
}

template <typename T>
int MyVector<T>::size() const{
    return count;
}

template <typename T>
void MyVector<T>::extendArray(){
    T *oldArray = array;
    Size *= 2;
    array = new T[Size];
    for (int i = 0; i < count; i++){
        array[i] = oldArray[i];
    }
    delete[] oldArray;
}
//Copy constructor
template<typename T>
MyVector<T>::MyVector(const MyVector<T> & src){
    this->array = new T[src.Size];
    count = src.count;
    Size = src.Size;
    for (int i = 0; i < src.count; i++){
        array[i] = src.array[i];
    }
}
//function of operator '='
template<typename T>
MyVector<T> & MyVector<T>::operator =(const MyVector<T> & src){
    delete[] array;
    this->array = new T[src.Size];
    count = src.count;
    Size = src.Size;
    for (int i = 0; i < src.count; i++){
        array[i] = src.array[i];
    }
    return *this;
}
//destructor
template<typename T>
MyVector<T>::~MyVector(){
    count = 0;
    delete [] array;
}

#endif // MYVECTOR

