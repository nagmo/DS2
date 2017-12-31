
#include "Colosseum.h"
using ColosseumException::Failure;
using ColosseumException::InvaldInput;


void validateIds(int n, int* ids){
    for (int i = 0; i < n; ++i) {
        if(ids[i] < 0) throw InvaldInput();
    }
}

Colosseum::Colosseum(int n, int* ids){
    validateIds(n, ids);
    //now ids are valid
    //TODO: should we check that new succeed and if not delete groups?
    TrainingGroup** groupIds = new TrainingGroup*[n]();
    for (int i = 0; i < n; ++i) {
        groupIds[i] = new TrainingGroup(ids[i]);
    }
    //dont check with try because we assume that id are valid
    heapGroup = MinHeap(n, groupIds);
    //delete heap groups
    for(int i=0; i<n; i++){
        delete groupIds[i];
    }
    delete [] groupIds;

    HashTrainingGroup** hashTrainingGroup = new HashTrainingGroup*[n];
    for (int k = 0; k < n; ++k) {
        //TODO: check if it is ok
        hashTrainingGroup[k] = new HashTrainingGroup(ids[k]);
    }
    hashGroup = TrainingGroupHashTable(n, hashTrainingGroup);
    //deleteing hash groups
    for(int i=0; i<n; i++){
        delete hashTrainingGroup[i];
    }
    delete [] hashTrainingGroup;
}

void Colosseum::addGroup(GroupId id){
    //check that id is valid
    if(id < 0) throw InvaldInput();
    HashTrainingGroup* group = new HashTrainingGroup(id);
    int index = -1;
    try{
        index = hashGroup.AddTrainingGroup(group);
    }
    catch (HashTableException::GroupAlreadyExist){
        delete group;
        throw InvaldInput();
    }
    delete group;
    TrainingGroup trainingGroup(id);
    //get the pointer to the group
    TrainingGroup& newGroup = heapGroup.addGroup(trainingGroup);
    if(index != -1){
        //TODO: change the index of the saved group in the hash
    }
    //TODO what if -1?
}

void Colosseum::addGlad(GladiatorID gladiatorID, Level level, GroupId groupId){
    Gladiator gladiator = Gladiator(gladiatorID, level);
    //add glad to hash
    try{
        hashGroup.AddGladiatorToTrainingGroup(gladiator, groupId);
    }
    catch (HashTableException::GroupAlreadyExist&){
        throw Failure();
    }
}

void Colosseum::fight(GroupId id1, GroupId id2, int i, int j){
    HashTrainingGroup trainingGroup;
    try{
        trainingGroup = hashGroup.TrainingGroupFight(id1, id2, i, j);
    }
    catch (HashTableException::GroupDoesntExist&){
        throw Failure();
    }
    catch (HashTableException::NotEnoghGladiators){
        throw Failure();
    }
    //disactivate the loosing teem
    heapGroup.disActiveGroup(trainingGroup.getIndex());
}

int Colosseum::getMinTrainingGroup(){
    TrainingGroup& trainingGroup = heapGroup.getMinGroup();
    if(trainingGroup.isVoid()) throw Failure();
    return trainingGroup.GetID();
}
