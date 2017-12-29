#ifndef DS2_DYNAMICARRAY_H
#define DS2_DYNAMICARRAY_H


#include <cstdio>

//TODO: Nevo - I think we should change it to exceptions
enum ArrayReturnValues{
    ArraySuccess,
    ArrayExpand,
};

/**
 * Generic class of Dynamic Array
 * T implements IsVoid() method
 * T has an empty constructor T() that creates a "void T"
 * T has copy c'tor
 */
template<class T>
class DynamicArray {
public:

    DynamicArray(int n);

    DynamicArray(int n, T* arr);

    ~DynamicArray();

    T& operator[](int index);

    ArrayReturnValues insert(T& data, int index);

    void swap(int i, int j);

    bool isEmpty(int index);

    int getMinOfThreeIndexes(int i, int j, int k);
    
    int length();

private:
    T* data;
    int maxSize;
    int numberOfElements;

    /**
     * make the array twice bigger
     */
    void extractArray();
};

template <class T>
DynamicArray<T>::DynamicArray(int n) : maxSize(n), numberOfElements(0){
    data = new T[n];
}

template <class T>
DynamicArray<T>::DynamicArray(int n, T* arr) : maxSize(n*2), numberOfElements(n){
    data = new T[n*2];
    for (int i = 0; i < n; ++i) {
        data[i] = arr[i];
    }
}


template <class T>
DynamicArray<T>::~DynamicArray(){
    delete [] data;
}


template <class T>
ArrayReturnValues DynamicArray<T>::insert(T& newData, int index){
    //case of new data - add 1 to items
    if(data[index].isVoid()) numberOfElements++;
    //delete data[index];
    data[index] = T(newData);
    //check if need expand
    if(numberOfElements >= maxSize/2){
        extractArray();
        return ArrayExpand;
    }
    return ArraySuccess;
}

template <class T>
void DynamicArray<T>::swap(int i, int j){
    //creating temp with copy c'tor
    T temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

template <class T>
T& DynamicArray<T>::operator[](int index){
    return data[index];
}

template <class T>
bool DynamicArray<T>::isEmpty(int index){
    return data[index].isVoid();
}


template <class T>
int DynamicArray<T>::length(){
    return maxSize;
}

template <class T>
int DynamicArray<T>::getMinOfThreeIndexes(int i, int j, int k){
    if(data[i] < data[j]){
        if(data[i] < data[k]) return i;
        return k;
    }
    return (data[j] < data[k]) ? j : k;
}

/**
 * make the array twice bigger
 */
template <class T>
void DynamicArray<T>::extractArray(){
    T* newArray = new T[2*maxSize];
    for (int i = 0; i < maxSize; ++i) {
        newArray[i] = data[i];
    }
    delete [] data;
    data = newArray;
    maxSize *= 2;
}

#endif //DS2_DYNAMICARRAY_H
