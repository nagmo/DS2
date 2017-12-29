
#include "MinHeap.h"

MinHeap::MinHeap(int n, int* idsArray) : data(DynamicArray<GroupId>(n, idsArray)){
    for (int i = n/2 - 1; i >= 0 ; i--) {
        siftDown(i);
        for (int j = 0; j < n; ++j) {
            printf("%d ", data[j]);
        }
        printf("\n");
    }
}

void MinHeap::siftDown(int i){
    data.swap(i, data.getMinOfThreeIndexes(i, i * 2 + 1, (i + 1) * 2));
}