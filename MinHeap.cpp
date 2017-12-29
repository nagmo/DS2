
#include "MinHeap.h"

using MinHeapExceptions::FailureException;


MinHeap::MinHeap(int n, TrainingGroup* idsArray) : data(DynamicArray<TrainingGroup>(n, idsArray)){
    for (int i = n/2 - 1; i >= 0 ; i--) {
        siftDown(i);
    }
}

void MinHeap::addGroup(TrainingGroup& trainingGroup){
    int numOfElements =  data.numOfElements();
    data.insert(trainingGroup, numOfElements);
    //now numOfelements is one bigger
    siftUp(numOfElements);
}

TrainingGroup& MinHeap::getMinGroup(){
    if(data.numOfElements() == 0) throw FailureException();
    return data[0];
}

void MinHeap::siftDown(int i){
    if(i > data.numOfElements()/2) return;
    int newIndex = data.getMinOfThreeIndexes(i, i * 2 + 1, (i + 1) * 2);
    if(newIndex == i) return;
    data.swap(i, newIndex);
    siftDown(newIndex);
}

void MinHeap::siftUp(int i){
    while (data[i] < data[i/2]){
        data.swap(i,i/2);
        i /= 2;
    }
}