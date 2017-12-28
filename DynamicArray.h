#ifndef DS2_DYNAMICARRAY_H
#define DS2_DYNAMICARRAY_H

/**
 * Generic class of Dynamic Array
 * The user have to call "extract" and "slice"
 */
Template<class T>
class DynamicArray {
public:

    DynamicArray(int n) : maxSize(0){
        data = new T[n];
    }

    ~DynamicArray(){
        delete [] data;
    }


    T& operator[](int index){
        return data[index];
    }

    /**
     * make the array twice bigger
     */
    void extractArray(){
        T* newArray = new T[2*maxSize](data);
        delete [] data;
        data = newArray;
        maxSize = 2*maxSize;
    }

    /**
    * make the array half size
    */
    void sliceArray(){
        T* newArray = new T[maxSize/2](data);
        delete [] data;
        data = newArray;
        maxSize = maxSize/2;
    }

    int length(){
        return maxSize;
    }
private:
    T data;
    int maxSize;
};


#endif //DS2_DYNAMICARRAY_H
