#ifndef DS2_DYNAMICARRAY_H
#define DS2_DYNAMICARRAY_H

//#include <clocale>
#include "utilities.h"

/**
 * Generic class of Dynamic Array
 * T implements IsVoid() method
 * T has an empty constructor T() that creates a "void T"
 * T has copy c'tor
 */
template<class T>
class DynamicArray {
public:
    /**
     * creates array size n
     * @param n
     */
    explicit DynamicArray(int n);

    /**
     * fill the array with the given values
     * @param n
     * @param arr
     */
    DynamicArray(int n, T** arr);

    ~DynamicArray();

    /**
     * returns the element in the index
     * @param index
     * @return
     */
    T& operator[](int index);

    /**
     * add new value to the array
     * @param data
     * @param index
     * @return expand - if there was array expansion
     */
    T* insert(T& data, int index);

    /**
     * swap values in the i j indexes
     * @param i
     * @param j
     */
    void swap(int i, int j);

    /**
     * check if cell is empty
     */
    bool isEmpty(int index);

    /**
     * returns the index of the minimal value from the i j k indexes
     * @param i
     * @param j
     * @param k
     * @return
     */
    int getMinOfThreeIndexes(int i, int j, int k);
    
    int length();

    /**
     * returns the number of elements in the array
     * @return
     */
    int numOfElements();

private:
    T** data;
    int maxSize;
    int numberOfElements;

    /**
     * make the array twice bigger
     */
    void expandArray();
};

namespace DynamicArrayException{
    class ArrayExpand : std::exception{
    public:
        ArrayExpand(void* object) : exception(){
            returnValue = object;
        }
        void* getObject(){
            return returnValue;
        }

    private:
        void* returnValue;
    };
}

template <class T>
DynamicArray<T>::DynamicArray(int n) : maxSize(n), numberOfElements(0){
    data = new T*[n](); //TODO: Yuval - this calls the default constructor for each element in the array. in this case because it's a pointer it puts NULL.
}

template <class T>
DynamicArray<T>::DynamicArray(int n, T** arr) : maxSize(n*2), numberOfElements(n){
    data = new T*[n*2]();
    for (int i = 0; i < n; ++i) {
        data[i] = new T(*(arr[i]));
    }
    for (int i = n; i < maxSize ; i++) {
        data[i] = new T();
    }
}


template <class T>
DynamicArray<T>::~DynamicArray(){
    for (int i = 0; i < maxSize; ++i) {
        delete data[i];
    }
    delete [] data;
}


template <class T>
T* DynamicArray<T>::insert(T& newData, int index){
    //case of new data - add 1 to items
    if(data[index] && (data[index])->isVoid()) numberOfElements++;
    //delete data[index];
    data[index] = new T(newData);
    //check if need expand
    if(numberOfElements >= maxSize/2){
        expandArray();
        //TODO if throws exception, return no data - Nevo: didn't get you
        throw DynamicArrayException::ArrayExpand(data[index]);
    }
    return (data[index]);
}

template <class T>
void DynamicArray<T>::swap(int i, int j){
    //creating temp with copy c'tor
    T* temp = data[i];
    data[i] = data[j];
    data[j] = temp;
}

template <class T>
T& DynamicArray<T>::operator[](int index){
    return *(data[index]);
}

template <class T>
bool DynamicArray<T>::isEmpty(int index){
    if(data!=NULL && data[index]!=NULL) return data[index]->isVoid();
    return true;
}


template <class T>
int DynamicArray<T>::length(){
    return maxSize;
}
template <class T>
int DynamicArray<T>::numOfElements(){
    return numberOfElements;
}

template <class T>
int DynamicArray<T>::getMinOfThreeIndexes(int i, int j, int k){
    //case of k is void (i cant be void)
    if(data[j] && data[j]->isVoid()) return i;
    if(data[k] && data[k]->isVoid()) return ((*data[i]) < (*data[j])) ? i : j;
    if(*data[i] < *data[j]){
        if(*data[i] < *data[k]) return i;
        return k;
    }
    return (*data[j] < *data[k]) ? j : k;
}

/**
 * make the array twice bigger
 */
template <class T>
void DynamicArray<T>::expandArray(){
    T** newArray = new T*[2*maxSize];
    for (int i = 0; i < maxSize; ++i) {
        newArray[i] = data[i];
    }
    //fill with empty values
    for(int i = maxSize; i < maxSize*2; i++){
        newArray[i] = new T();
    }
    delete [] data;
    data = newArray;
    maxSize *= 2;
}

#endif //DS2_DYNAMICARRAY_H
