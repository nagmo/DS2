#ifndef DS2_MINHEAP_H
#define DS2_MINHEAP_H

#include "DynamicArray.h"
#include "TrainingGroup.h"
#include "utilities.h"

class MinHeap {
public:
    MinHeap(int n, TrainingGroup* idsArray);

    void addGroup(TrainingGroup& trainingGroup);

    TrainingGroup& getMinGroup();

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
