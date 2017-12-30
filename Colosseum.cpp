
#include "Colosseum.h"

Colosseum::Colosseum(int n, int* ids) : heapGroup(){
    TrainingGroup** groupIds = new TrainingGroup*[n];
    for (int i = 0; i < n; ++i) {
        groupIds[i] = new TrainingGroup(ids[i]);
    }
    heapGroup = MinHeap(n, groupIds);
    hashGroup = HashTrainingGroup();
}

void Colosseum::addGroup(GroupId id){
    //check that id is valid
}

void Colosseum::addGlad(GladiatorID, Level, GroupId);

void Colosseum::fight(GroupId, GroupId, int, int);

void Colosseum::getMinTrainingGroup(int*);