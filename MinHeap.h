#ifndef DS2_MINHEAP_H
#define DS2_MINHEAP_H

#include "DynamicArray.h"
#include "TrainingGroup.h"
#include "utilities.h"

class MinHeap {
public:
    MinHeap(int n, int* idsArray);

    void siftDown(int i);


private:
    DynamicArray<GroupId> data;
};


#endif //DS2_MINHEAP_H
