
#include "Colosseum.h"
using ColosseumException::Failure;
using ColosseumException::InvaldInput;


void validateIds(int n, int* ids){
    for (int i = 0; i < n; ++i) {
        if(ids[i] < 0) throw InvaldInput();
    }
}

Colosseum::Colosseum(int n, int* ids) : heapGroup(){
    validateIds(n, ids);
    //now ids are valid
    //TODO: should we check that new succeed and if not delete groups?
    TrainingGroup** groupIds = new TrainingGroup*[n];
    for (int i = 0; i < n; ++i) {
        groupIds[i] = new TrainingGroup(ids[i]);
    }
    try{
        heapGroup = MinHeap(n, groupIds);
    }
    catch (MinHeapExceptions::FailureException&){
        for (int i = 0; i < n; ++i) {
            delete groupIds[i];
        }
    }
    //dont check with try because we assume that id are valid
    HashTrainingGroup* hashTrainingGroup = new HashTrainingGroup[n];
    for (int k = 0; k < n; ++k) {
        //TODO: check if it is ok
        hashTrainingGroup[k] = HashTrainingGroup(ids[k]);
    }

    hashGroup = TrainingGroupHashTable(n, hashTrainingGroup);
    //deleteing the groups
    delete [] hashTrainingGroup;
    for (int j = 0; j < n; ++j) {
        delete groupIds[j];
    }
    delete [] groupIds;
}

void Colosseum::addGroup(GroupId id){
    //check that id is valid
    if(id < 0) throw InvaldInput();
    HashTrainingGroup group = HashTrainingGroup(id);
    try{
        hashGroup.AddTrainingGroup(group);
    }
    catch (HashTableException::GroupAlreadyExist){
        throw InvaldInput();
    }
    TrainingGroup trainingGroup = TrainingGroup(id);
    //get the pointer to the group
    TrainingGroup& newGroup = heapGroup.addGroup(trainingGroup);
    hashGroup.

}

void Colosseum::addGlad(GladiatorID, Level, GroupId){}

void Colosseum::fight(GroupId, GroupId, int, int){}

void Colosseum::getMinTrainingGroup(int*){}

