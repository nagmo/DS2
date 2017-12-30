
#include "MinHeap.h"

using MinHeapExceptions::FailureException;


MinHeap::MinHeap(int n, TrainingGroup** idsArray) : data(DynamicArray<TrainingGroup>(n, idsArray)){
    //arrange the array
    for (int i = n/2 - 1; i >= 0 ; i--) {
        siftDown(i);
    }
    //set to each group its index in the array and the pointer to the heap
    int length = data.length();
    for (int i = 0; i < length; i++) {
        data[i].setIndex(i);
        data[i].setHeapPointer(this);
    }
}

TrainingGroup& MinHeap::addGroup(TrainingGroup& trainingGroup){
    int numOfElements =  data.numOfElements();
    TrainingGroup& newGroup = data.insert(trainingGroup, numOfElements);
    newGroup.setHeapPointer(this);
    //now numOfelements is one bigger
    siftUp(numOfElements);
    return newGroup;
}

TrainingGroup& MinHeap::getMinGroup(){
    if(data.numOfElements() == 0) throw FailureException();
    return data[0];
}

void MinHeap::disActiveGroup(int i){
    //disactivate group
    data[i].disActivate();
    //sift group down
    siftDown(i);
}

void MinHeap::siftDown(int i){
    if(i > data.numOfElements()/2) return;
    int newIndex = data.getMinOfThreeIndexes(i, i * 2 + 1, (i + 1) * 2);
    if(newIndex == i) return;
    //set the new index of the group
    data[i].setIndex(newIndex);
    data[newIndex].setIndex(i);
    data.swap(i, newIndex);
    siftDown(newIndex);
}

void MinHeap::siftUp(int i){
    while (data[i] < data[i/2]){
        //set the new index of the group
        data[i].setIndex(i/2);
        data[i/2].setIndex(i);
        //swapping
        data.swap(i,i/2);
        i /= 2;
    }
}