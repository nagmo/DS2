#ifndef DS2_DYNAMICARRAY_H
#define DS2_DYNAMICARRAY_H


#include <cstdio>

enum ArrayReturnValues{
    ArraySuccess,
    ArrayExpand,
    ArraySlice
};

/**
 * Generic class of Dynamic Array
 * T has to implement IsEmpty() and SetEmpty() - to an illegal value of T type
 * T has an empty constructor T()
 */
template<class T>
class DynamicArray {
public:

    DynamicArray(int n);

    ~DynamicArray();

    T& operator[](int index);

    ArrayReturnValues insert(T& data, int index);

    ArrayReturnValues remove(int index);

    int length();

private:
    T* data;
    int maxSize;
    int numberOfElements;

    /**
     * make the array twice bigger
     */
    void extractArray();

    /**
    * make the array half size
    */
    void sliceArray();
};

template <class T>
DynamicArray<T>::DynamicArray(int n) : maxSize(n), numberOfElements(0){
    data = new T[n];
    for(int i = 0; i < n; i++){
        data[i].SetEmpty();
    }
}

template <class T>
DynamicArray<T>::~DynamicArray(){
    delete [] data;
}


template <class T>
ArrayReturnValues DynamicArray<T>::insert(T& newData, int index){
    //case of new data - add 1 to items
    if(data[index].IsEmpty()) numberOfElements++;
    //delete data[index];
    data[index] = T(newData);
    //check if need expand
    if(numberOfElements > maxSize/2){
        extractArray();
        return ArrayExpand;
    }
    return ArraySuccess;
}

template <class T>
ArrayReturnValues DynamicArray<T>::remove(int index){
    //case of new data - add 1 to items
    if(data[index].IsEmpty())
        return ArraySuccess;
    numberOfElements--;
    data[index].SetEmpty();
    //check if need expand
    if(numberOfElements < maxSize/4){
        sliceArray();
        return ArraySlice;
    }
    return ArraySuccess;
}

template <class T>
T& DynamicArray<T>::operator[](int index){
    return data[index];
}

template <class T>
int DynamicArray<T>::length(){
    return maxSize;
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

/**
* make the array half size
*/
template <class T>
void DynamicArray<T>::sliceArray(){
    T* newArray = new T[maxSize/2];
    for (int i = 0; i < maxSize/2; ++i) {
        newArray[i] = data[i];
    }
    delete [] data;
    data = newArray;
    maxSize = maxSize/2;
}

#endif //DS2_DYNAMICARRAY_H
