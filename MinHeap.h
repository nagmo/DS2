#ifndef DS2_MINHEAP_H
#define DS2_MINHEAP_H

#include "DynamicArray.h"
#include "TrainingGroup.h"
#include "utilities.h"

class MinHeap {
public:
    explicit MinHeap();
    /**
     * create a heap from array
     * @param n - length
     * @param idsArray
     */
    MinHeap(int n, TrainingGroup** idsArray);

    /**
     * add new group to the heap
     * need to check if is exists before using this function
     * @param trainingGroup
     */
    TrainingGroup* addGroup(TrainingGroup& trainingGroup);

    /**
     * returns the minimal group that is active
     * @return
     */
    TrainingGroup& getMinGroup();

    void deActiveGroup(int);

    /**
     * very dangerous!! dont use it!
     * use only it the constructor of hashtable
     * @return
     */
    DynamicArray<TrainingGroup>* getDataArray();


private:
    DynamicArray<TrainingGroup> data;

    void siftDown(int i);

    void siftUp(int i);

};

namespace MinHeapExceptions{
    using std::exception;

    class FailureException : exception{};
}
#endif //DS2_MINHEAP_H
